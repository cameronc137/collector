//	Collector Output Reader
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

  gStyle->SetOptFit(1);

}
void Open(TString filename){
  TFile* rootfile = TFile::Open(filename);
}
void Show(TString channel_name, TCut user_cut=""){
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
  Int_t npt = run_tree->Draw("run:Entry$",user_cut,"goff");
  double* dummy = run_tree->GetV1();
  double* run =new double[npt];
  for(int ipt=0;ipt<npt;ipt++)
    run[ipt] = *(dummy+ipt);

  run_tree->Draw("mini:Entry$",user_cut,"goff");
  double* mini = new double[npt];
  dummy = run_tree->GetV1();
  for(int ipt=0;ipt<npt;ipt++)
    mini[ipt] = *(dummy+ipt);
  

  if(channel_name.Contains("mean")){
      npt=run_tree->Draw(channel_name+":Entry$",user_cut,"goff");
      double* mean = new double[npt];
      double* ent = new double[npt];
      dummy = run_tree->GetV1();
      for(int ipt=0;ipt<npt;ipt++)
	mean[ipt] = *(dummy+ipt);

      for(int ipt=0;ipt<npt;ipt++)
	ent[ipt] = ipt;
      
      TString channel_err = channel_name;
      channel_err.ReplaceAll("mean","err");
      npt=run_tree->Draw(channel_err+":Entry$",user_cut,"goff");
      dummy = run_tree->GetV1();
      double* err = new double[npt];
      double* x_err = new double[npt];
      for(int ipt=0;ipt<npt;ipt++){
	err[ipt] = *(dummy+ipt);
	x_err[ipt] = 0.0;
      }

      TGraphErrors* fGraph = new TGraphErrors(npt,
					      ent,mean,
					      x_err,err);
      fGraph->SetMarkerStyle(20);
      fGraph->Draw("AP");
      fGraph->Fit("pol0");
      fGraph->SetTitle(channel_name);
      fGraph->GetXaxis()->Set(npt,-0.5,npt-0.5);
      fGraph->GetXaxis()->SetTitle("Run.Mini");
      for(int ipt=0;ipt<npt;ipt++){
	fGraph->GetXaxis()->SetBinLabel(ipt+1,
					Form("%d.%d",(int)run[ipt],(int)mini[ipt]));
      }
    }
    else{
      npt=run_tree->Draw(channel_name+":Entry$",user_cut,"goff");
      Double_t *ent = new Double_t[npt];
      for(int ipt=0;ipt<npt;ipt++)
	ent[ipt] = ipt;

      TGraph* fGraph = new TGraph(npt,ent,run_tree->GetV1());
      fGraph->SetMarkerStyle(20);
      fGraph->Draw("AP");
      fGraph->SetTitle(channel_name);
      fGraph->GetXaxis()->Set(npt,-0.5,npt-0.5);
      fGraph->GetXaxis()->SetTitle("Run.Mini");
      for(int ipt=0;ipt<npt;ipt++){
	fGraph->GetXaxis()->SetBinLabel(ipt+1,
					Form("%d.%d",(int)run[ipt],(int)mini[ipt]));
      }
    }
}
