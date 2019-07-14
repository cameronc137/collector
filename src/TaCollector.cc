#include "TaInput.hh"
#include "TaCollector.hh"
//#include "TaOutput.hh"
#include <iostream>

TString dv_list[]=
  {"asym_usl",
   "asym_usr",
   "asym_dsl",
   "asym_dsr",
   "asym_us_avg",
   "asym_us_dd",
   "asym_ds_avg",
   "asym_ds_dd",
   "asym_left_avg",
   "asym_left_dd",
   "asym_right_avg",
   "asym_right_dd",
   "asym_bcm_an_ds3"};

TString iv_list[]=
  {"diff_bpm4aX",
   "diff_bpm4aY",
   "diff_bpm4eX",
   "diff_bpm4eY",
   "diff_bpm12X"};

ClassImp(TaCollector);
using namespace std;
TaCollector::TaCollector(){
  fInput= new TaInput();
}
TaCollector::TaCollector(TaInput *aInput){
  fInput= aInput;
  collection_file = new TFile("test.root","RECREATE");
}

TaCollector::~TaCollector(){
}

int TaCollector::Process(){
#ifdef NOISY
  cout << "--"
       << __PRETTY_FUNCTION__ << endl;
#endif
  col_tree = new TTree("T","Collection Tree");
  Int_t run_number,seg_number,mini_id;
  typedef struct {Double_t ppm,um;} UNIT;
  UNIT parity_scale;
  parity_scale.ppm = 1e-6;
  parity_scale.um = 1e-3;

  col_tree->Branch("run",&run_number,"run/I");
  col_tree->Branch("seg",&seg_number,"seg/I");
  col_tree->Branch("mini",&mini_id,"mini/I");
  col_tree->Branch("unit",&parity_scale,"ppm/D:um");
  
  typedef struct {Double_t mean,err,rms;} STATS;
  const int ndv = sizeof(dv_list)/sizeof(*dv_list);
  const int niv = sizeof(iv_list)/sizeof(*iv_list);
  STATS dv_raw_stat[ndv];
  STATS dv_reg_stat[ndv];
  STATS iv_stat[niv];
  Double_t slope[ndv][niv];
  Double_t slope_err[ndv][niv];
  
  for(int idv=0;idv<ndv;idv++){
    col_tree->Branch(dv_list[idv],
		     &dv_raw_stat[idv],
		     "mean/D:err:rms");
    TString name_buff =dv_list[idv];
    name_buff = name_buff.ReplaceAll("asym","reg_asym");
    col_tree->Branch(name_buff,
		     &dv_reg_stat[idv],
		     "mean/D:err:rms");
  }
  for(int iiv=0;iiv<niv;iiv++)
    col_tree->Branch(iv_list[iiv],
		     &iv_stat[iiv],
		     "mean/D:err:rms");
  col_tree->Branch("slope",slope,
		   Form("slope[%d][%d]/D",ndv,niv));
  col_tree->Branch("slope_err",slope_err,
		   Form("slope_err[%d][%d]/D",ndv,niv));
  
  vector<TString> filename_list = fInput->GetNameList();
  TString this_dir = fInput->GetDirectory();
  vector<TString>::iterator itfl =filename_list.begin();
  while(itfl!=filename_list.end()){
#ifdef NOISY
    cout << "-- Reading " << this_dir << *itfl << endl;
#endif
    TFile* this_file = TFile::Open(this_dir+"./"+(*itfl));
    TTree* mini_tree = (TTree*)this_file->Get("mini");
    if(mini_tree!=NULL){
      for(int idv=0;idv<ndv;idv++){
	mini_tree->SetBranchAddress(dv_list[idv],&dv_raw_stat[idv]);
	TString reg_name = dv_list[idv];
	reg_name.ReplaceAll("asym","reg_asym");
	mini_tree->SetBranchAddress(reg_name,&dv_reg_stat[idv]);
      }
      for(int iiv=0;iiv<niv;iiv++)
	mini_tree->SetBranchAddress(iv_list[iiv],&iv_stat[iiv]);
      mini_tree->SetBranchAddress("minirun",&mini_id);
      
      Int_t nentries = mini_tree->GetEntries();
      for(int ientry=0;ientry<nentries;ientry++){
	mini_tree->GetEntry(ientry);
	col_tree->Fill();
      }
    }
#ifdef NOISY    
    else
      cout << "mini run tree is not found in "
	   << *itfl
	   << ", so now skip to next one " << endl;
#endif
    this_file->Close();
    itfl++;
  }
    
  return 0;
}

int TaCollector::End(){
#ifdef NOISY
  cout << "--"
       << __PRETTY_FUNCTION__ << endl;
#endif
  collection_file->cd();
  col_tree->Write();
  collection_file->Close();
  return 0;
}