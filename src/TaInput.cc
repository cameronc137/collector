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
      nameList.push_back(sysfile->GetName());
    }// end of fileList Loop;
  }// end of if fileList Exist
  return 1;
}

int TaInput::RunListChoice(){
  // ========================================FIXME
  return 0;
}
