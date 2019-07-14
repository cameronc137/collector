#ifndef __TaCollector_hh_
#define __TaCollector_hh_
#include "TObject.h"
#include "TTree.h"
#include "TFile.h"
class TaInput;
//class TaOutput;
using namespace std;

class TaCollector: public TObject{

public:
  //method
  TaCollector();
  TaCollector(TaInput* aInput);
  ~TaCollector();

  int Process();
  int End();
  
  //data
  
private:
  //method
  TFile* collection_file;
  TTree* col_tree;
  //TTree* run_tree;
  //TTree* slug_tree;
  //data
  TaInput* fInput;
  TString outputName;
  //  TaOutput* fOutput;

  ClassDef(TaCollector,0);
};
#endif
