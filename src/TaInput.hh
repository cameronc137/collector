#ifndef __TaInput_hh__
#define __TaInput_hh__

#include <vector>
#include "TObject.h"
#include "TString.h"

using namespace std;
class TaInput: public TObject{
public:
  TaInput();
  ~TaInput();

  //method
  void LoadConfig();
  int SearchFiles();
  int RunListChoice();
  
  inline void ToggleSnapshot(Bool_t is){isSnapshotMode=is;};
  inline void SetDirectory(TString dir){target_dir=dir;};
  inline void SetRunList(TString name){list_name=name;}
  inline void SetRunListDefined(){isRunListDefined=kTRUE;};
  inline Bool_t IsRunListDefined(){return isRunListDefined;};
  inline Bool_t GetSnapshotMode(){return isSnapshotMode;};
  inline vector<TString> GetNameList(){return nameList;};
  inline TString GetDirectory(){return target_dir;};
  inline TString GetListFileName(){return list_name;};
  //data

private:
  // data
  Bool_t isSnapshotMode;
  Bool_t isRunListDefined;
  TString target_dir;
  TString list_name;
  vector<TString> nameList;
  vector<Int_t> defined_list;
  ClassDef(TaInput,0);
};

#endif
