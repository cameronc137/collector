#include "TaInput.hh"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TList.h"

#include <iostream>

ClassImp(TaInput);
using namespace std;

TaInput::TaInput(){
  isSnapshotMode=kFALSE;
  isRunListDefined=kFALSE;
  target_dir= "./results";
  list_name="";
}

TaInput::~TaInput(){
}
void TaInput::LoadConfig(){
  if(isRunListDefined)
    RunListChoice();
  SearchFiles();
}
int TaInput::SearchFiles(){
#ifdef NOISY
  cout <<"--"
       << __PRETTY_FUNCTION__ << endl;
#endif
  const char* dir_name = "";
  const char* path= target_dir.Data();
  TSystemDirectory *sysDir = new TSystemDirectory(dir_name,path);
  TList* fileList = sysDir->GetListOfFiles();
  if(fileList){
    TIter next(fileList);
    TSystemFile* sysfile;
    while( (sysfile=(TSystemFile*)next()) ){
      if(sysfile->IsDirectory()){
	fileList->Remove(sysfile);
	continue;
      }
      TString name_buff = sysfile->GetName();
      if(!(name_buff.Contains(".root"))){
	 fileList->Remove(sysfile);
	 continue;
      }
      if(!(name_buff.Contains("prex"))){
	fileList->Remove(sysfile);
	continue;
      }
    }// end of fileList Loop;
    TIter iter(fileList);
    fileList->Sort();
    while( (sysfile=(TSystemFile*)iter()) ){
#ifdef NOISY
      cout << "-- Found file " << sysfile->GetName() << endl;
#endif
      if(isRunListDefined){
	Bool_t kMatched = kFALSE;
	TString sysfile_name = sysfile->GetName();
	vector<Int_t>::iterator iter = defined_list.begin();
	while(iter!=defined_list.end()){
	  if(sysfile_name.Contains(Form("%d",*iter))){
	    kMatched = kTRUE;
	    break;
	  }
	  iter++;
	}
	if(kMatched){
#ifdef NOISY	  
	  cout << "-- Matched "
	       << sysfile_name 
	       << " specified in the run list" << endl;
#endif
	  nameList.push_back(sysfile_name);
	}
      }
      else
	nameList.push_back(sysfile->GetName());
    }// end of fileList Loop;
  }// end of if fileList Exist
  return 1;
}

int TaInput::RunListChoice(){
  FILE* listfile = fopen(list_name.Data(),"r");
  if(listfile==NULL){
    cout << "-- Error: failed to open " << list_name  << endl;
    return 1;
  }
  else{
    int buff;
    while(!feof(listfile)){
      fscanf(listfile,"%d\n",&buff);
#ifdef DEBUG
      cout << "Get RunList candidate: " << buff << endl;
#endif
      defined_list.push_back(buff);
    }
    fclose(listfile);
    return 0;
  }
}
