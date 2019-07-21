#include "TaInput.hh"
#include "TaCollector.hh"
#include "TDatime.h"
#include "TString.h"
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
   "asym_bcm_an_ds",
   "asym_bcm_an_ds3",
   "asym_bcm_an_us",
   "asym_bcm_dg_ds",
   "asym_bcm_dg_us",
   "asym_cav4cQ",
   "bcm_an_us_ds_avg",
   "bcm_an_us_ds_dd",
   "bcm_an_us_ds3_avg",
   "bcm_an_us_ds3_dd",
   "bcm_an_ds_ds3_avg",
   "bcm_an_ds_ds3_dd",
   "bcm_dg_us_ds_avg",
   "bcm_dg_us_ds_dd",
   "bcm_dg_us_ds3_avg",
   "bcm_dg_us_ds3_dd",
   "bcm_dg_ds_ds_avg",
   "bcm_dg_ds_ds_dd",
   "bcm_dg_ds_ds3_avg",
   "bcm_dg_ds_ds3_dd",
   "bcm_cav4cQ_ds_avg",
   "bcm_cav4cQ_ds_dd",
   "bcm_cav4cQ_ds3_avg",
   "bcm_cav4cQ_ds3_dd",
   "asym_sam1",
   "asym_sam2",
   "asym_sam3",
   "asym_sam4",
   "asym_sam5",
   "asym_sam6",
   "asym_sam7",
   "asym_sam8",
   "asym_sam_15_avg",
   "asym_sam_15_dd",
   "asym_sam_37_avg",
   "asym_sam_37_dd",
   "asym_sam_26_avg",
   "asym_sam_26_dd",
   "asym_sam_48_avg",
   "asym_sam_48_dd"};

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
  TDatime* nowTime = new TDatime();
  if(fInput->IsRunListDefined()){
    TString list_filename = fInput->GetListFileName();
    Ssiz_t last = list_filename.Last('.')-1;
    Ssiz_t first = list_filename.Last('/')+1;
    Ssiz_t length_t = last - first+1;
    TString filename_stem = list_filename(first,length_t);
    outputName = Form("rootfiles/prexPrompt_%s.root",
		      filename_stem.Data());
  }
  else
    outputName = Form("rootfiles/prexPrompt_%d_snapshot.root",
		      nowTime->GetDate());
		      
  collection_file = new TFile(outputName,"RECREATE");
  
}

TaCollector::~TaCollector(){
}

int TaCollector::Process(){
#ifdef NOISY
  cout << "--"
       << __PRETTY_FUNCTION__ << endl;
#endif
  col_tree = new TTree("T","Collection Tree");
  col_tree->SetMarkerStyle(20);
  Int_t run_number,seg_number,mini_id;
  typedef struct {Double_t ppm,ppb,um,nm;} UNIT;
  UNIT parity_scale;
  parity_scale.ppm = 1e-6;
  parity_scale.ppb = 1e-9;
  parity_scale.um = 1e-3;
  parity_scale.nm = 1e-6;

  col_tree->Branch("run",&run_number,"run/I");
  col_tree->Branch("seg",&seg_number,"seg/I");
  col_tree->Branch("mini",&mini_id,"mini/I");
  col_tree->Branch("unit",&parity_scale,"ppm/D:ppb:um:nm");
  
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
    name_buff = "reg_"+name_buff;
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
    TFile* redfile = TFile::Open(this_dir+"/"+(*itfl));
    if(redfile==NULL){
      cout << "-- Warning: failed to open "
	   << *itfl
	   << endl;
      itfl++;
      continue;
    }

    vector<TString> *DVNames = (vector<TString>*)redfile->Get("DVNames");
    vector<TString> *IVNames = (vector<TString>*)redfile->Get("IVNames");
    if(DVNames==NULL || IVNames==NULL){
      cout << "-- Warning: DVNames or IVNames are "
	   << "not registerd in postpan file "
	   << endl;
      itfl++;
      continue;
    }
    Int_t* dv_map = new Int_t[ndv];
    Int_t* iv_map = new Int_t[niv];
    Bool_t kFileMatched = kTRUE;
    for(int idv=0;idv<ndv;idv++){
      vector<TString>::iterator iter_dv = (*DVNames).begin();
      Bool_t kMatched = kFALSE;
      while(iter_dv!=(*DVNames).end()){
	if(dv_list[idv]==(*iter_dv)){
	  dv_map[idv]=iter_dv-(*DVNames).begin();
	  kMatched = kTRUE;
#ifdef DEBUG
	  cout << "-- Mapping list index: " 
	       << idv
	       << " to redfile list index: "
	       << dv_map[idv] << endl;
#endif
	  break;
	}
	iter_dv++;
      }
      if(!kMatched){
	dv_map[idv]=-1;
#ifdef NOISY
	cout << "-- kFileMatched faile " <<endl;
#endif
	kFileMatched = kFALSE;
	break;
      }
    }
    for(int iiv=0;iiv<niv;iiv++){
      vector<TString>::iterator iter_iv = (*IVNames).begin();
      Bool_t kMatched = kFALSE;
      while(iter_iv!=(*IVNames).end()){
	if(iv_list[iiv]==(*iter_iv)){
	  iv_map[iiv]=iter_iv-(*IVNames).begin();
#ifdef DEBUG
	  cout << "-- Mapping list index: " 
	       << iiv 
	       << " to redfile list index: "
	       << iv_map[iiv] << endl;
#endif
	  kMatched = kTRUE;
	  break;
	}
	iter_iv++;
      }
      if(!kMatched){
	dv_map[iiv]=-1;
#ifdef NOISY
	cout << "-- kFileMatched failed " <<endl;
#endif
	kFileMatched = kFALSE;
	break;
	}
    }
    if(!kFileMatched){
      cout << "-- Error: DV or IV list doesn't match default list. " << endl;
      redfile->Close();
      itfl++;
      continue;
	}
    TTree* mini_tree = (TTree*)redfile->Get("mini");
    if(mini_tree!=NULL){
      for(int idv=0;idv<ndv;idv++){
	mini_tree->SetBranchAddress(dv_list[idv],&dv_raw_stat[idv]);
	TString reg_name = dv_list[idv];
	reg_name = "reg_"+reg_name;
	mini_tree->SetBranchAddress(reg_name,&dv_reg_stat[idv]);
      }
      for(int iiv=0;iiv<niv;iiv++)
	mini_tree->SetBranchAddress(iv_list[iiv],&iv_stat[iiv]);
      
      const Int_t ndv_red = (*DVNames).size();
      const Int_t niv_red = (*IVNames).size();
      Double_t coeff[ndv_red][niv_red];
      Double_t coeff_err[ndv_red][niv_red];
      mini_tree->SetBranchAddress("coeff",coeff);
      mini_tree->SetBranchAddress("err_coeff",coeff_err);

      mini_tree->SetBranchAddress("minirun",&mini_id);
      mini_tree->SetBranchAddress("run_number",&run_number);
      mini_tree->SetBranchAddress("seg_number",&seg_number);
      Int_t nentries = mini_tree->GetEntries();
      for(int ientry=0;ientry<nentries;ientry++){
	mini_tree->GetEntry(ientry);
	for(int idv=0;idv<ndv;idv++){
	  for(int iiv=0;iiv<niv;iiv++){
	  slope[idv][iiv] = coeff[dv_map[idv]][iv_map[iiv]];
	  slope_err[idv][iiv] = coeff_err[dv_map[idv]][iv_map[iiv]];
	  }
	}
	col_tree->Fill();
      }
    }
#ifdef NOISY    
    else
      cout << "mini run tree is not found in "
	   << *itfl
	   << ", so now skip to next one " << endl;
#endif
    redfile->Close();
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
