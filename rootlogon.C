// 	Collector Output Reader
//	author : Tao Ye	
//	Last update :  July 2019

//	Collector Output Reader
// 	- postpan regression output reader macro
//	author : Tao Ye	
//	Last update :  July 2019

void rootlogon(){
  cout << " ----------------------------------------------" <<endl;
  cout << "Collector Output Reader" << endl;
  cout << "Example : "<< endl;
  cout << "	\t Step1. Open(\"prexPrompt_20190714Swing.root\") "<< endl;
  cout << "	\t Step2.  "<< endl;
  cout << "	\t Show(\"reg_asym_usl.rms/ppm\") "<< endl;
  cout << "	\t Show(\"diff_bpm4aX.rms/um\") "<< endl;
  cout << "	\t Show(\"usl_bpm4aX/(ppm/um)\") "<< endl;
  cout << " ----------------------------------------------\n" <<endl;
  

}
void Open(TString filename){
  TFile* rootfile = TFile::Open(filename);
}
void Show(TString channel_name){
  TTree* run_tree = (TTree*)gDirectory->Get("T");  
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
  Int_t nIV = sizeof(iv_list)/sizeof(*iv_list);
  Int_t nDV = sizeof(dv_list)/sizeof(*dv_list);

  TString dv_name, iv_name;
  for(Int_t idv=0;idv<nDV;idv++){
    for(Int_t iiv=0;iiv<nIV;iiv++){
      dv_name = dv_list[idv];
      iv_name = iv_list[iiv];
      dv_name.ReplaceAll("asym_","");
      iv_name.ReplaceAll("diff_","");
      TString coeff_name = Form("slope[%d][%d]",idv,iiv);
      run_tree->SetAlias(Form("%s_%s",dv_name.Data(),iv_name.Data()),
			 coeff_name);
    }
  }
  TCanvas *c1 = new TCanvas("c1","c1",1200,600);
  c1->SetGridx();
  c1->SetGridy();
  Int_t npt = run_tree->Draw("run:Entry$","","goff");
  double* dummy = run_tree->GetV1();
  double* run =new double[npt];
  for(int ipt=0;ipt<npt;ipt++)
    run[ipt] = *(dummy+ipt);

  run_tree->Draw("mini:Entry$","","goff");
  double* mini = new double[npt];
  dummy = run_tree->GetV1();
  for(int ipt=0;ipt<npt;ipt++)
    mini[ipt] = *(dummy+ipt);
  
  run_tree->Draw(channel_name+":Entry$");
  TH2D* h_buff = (TH2D*)gPad->FindObject("htemp");
  if(h_buff!=NULL){
    h_buff->GetXaxis()->SetTitle("Run.Mini");
    for(int ipt=0;ipt<npt;ipt++){
      h_buff->GetXaxis()->SetBinLabel(ipt+1,
				      Form("%d.%d",(int)run[ipt],(int)mini[ipt]));
    }
  }
  else
    cout << channel_name << " Not Found" << endl;
}
