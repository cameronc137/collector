/**********************************   
Data Statistics Collector for 
Post-Parity Analyzer Outputs
	author: Tao Ye
	<tao.ye@stonybrook.edu>
	last update: July 2019
************************************/
#include "TaInput.hh"
#include "TaCollector.hh"
#include <iostream>

using namespace std;
int main(int argc, char** argv){
  
  cout << "\n*********************************************** " <<endl;
  cout << "Data Statistics Collector for " <<endl;
  cout << "Post-Parity Analyzer Outputs" <<endl;
  cout<< "\t author: Tao Ye " << endl;
  cout<< "\t <tao.ye@stonybrook.edu>" << endl;
  cout<< "\t last update: July 2019" << endl;
  cout << "***********************************************\n " <<endl;

  int opt;
  TString starget_dir;
  TString slist_name;
  enum EStatus{status_ok,status_fail};
  EStatus kStatus =status_ok;
  
  Bool_t isDirectoryDefined = kFALSE;
  Bool_t isRunListDefined = kFALSE;
  Bool_t isSnapshotMode = kFALSE;
  
  while( (opt=getopt(argc,argv,":d:l:s"))!=-1){
    switch(opt){
    case ':':
      cout << argv[optind-1] << "requires value. " <<endl;
      kStatus = status_fail;
      break;
    case '?':
      cout << "Unknown arguments " <<optopt << endl;
      kStatus = status_fail;
      break;
    case 'd':
      starget_dir = TString(optarg);
      isDirectoryDefined = kTRUE;
      break;
    case 'l':
      slist_name = TString(optarg);
      isRunListDefined = kTRUE;
      break;
    case 's':
      isSnapshotMode=kTRUE;
      break;
    }
  }
  
  if(kStatus==status_fail)
    return 1;

  TaInput* fInput = new TaInput();
  if(isDirectoryDefined)
    fInput->SetDirectory(starget_dir);
  if(isRunListDefined)
    fInput->SetRunList(slist_name);
  fInput->ToggleSnapshot(isSnapshotMode);
  fInput->LoadConfig();
  
  TaCollector* fCollector = new TaCollector(fInput);
  fCollector->Process();
  fCollector->End();
  
  return 0;
}
