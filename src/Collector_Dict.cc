// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME Collector_Dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TaInput.hh"
#include "TaCollector.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TaInput(void *p = 0);
   static void *newArray_TaInput(Long_t size, void *p);
   static void delete_TaInput(void *p);
   static void deleteArray_TaInput(void *p);
   static void destruct_TaInput(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TaInput*)
   {
      ::TaInput *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TaInput >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TaInput", ::TaInput::Class_Version(), "TaInput.hh", 9,
                  typeid(::TaInput), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TaInput::Dictionary, isa_proxy, 4,
                  sizeof(::TaInput) );
      instance.SetNew(&new_TaInput);
      instance.SetNewArray(&newArray_TaInput);
      instance.SetDelete(&delete_TaInput);
      instance.SetDeleteArray(&deleteArray_TaInput);
      instance.SetDestructor(&destruct_TaInput);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TaInput*)
   {
      return GenerateInitInstanceLocal((::TaInput*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TaInput*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TaCollector(void *p = 0);
   static void *newArray_TaCollector(Long_t size, void *p);
   static void delete_TaCollector(void *p);
   static void deleteArray_TaCollector(void *p);
   static void destruct_TaCollector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TaCollector*)
   {
      ::TaCollector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TaCollector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TaCollector", ::TaCollector::Class_Version(), "TaCollector.hh", 10,
                  typeid(::TaCollector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TaCollector::Dictionary, isa_proxy, 4,
                  sizeof(::TaCollector) );
      instance.SetNew(&new_TaCollector);
      instance.SetNewArray(&newArray_TaCollector);
      instance.SetDelete(&delete_TaCollector);
      instance.SetDeleteArray(&deleteArray_TaCollector);
      instance.SetDestructor(&destruct_TaCollector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TaCollector*)
   {
      return GenerateInitInstanceLocal((::TaCollector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TaCollector*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TaInput::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TaInput::Class_Name()
{
   return "TaInput";
}

//______________________________________________________________________________
const char *TaInput::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TaInput*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TaInput::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TaInput*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TaInput::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TaInput*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TaInput::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TaInput*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TaCollector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TaCollector::Class_Name()
{
   return "TaCollector";
}

//______________________________________________________________________________
const char *TaCollector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TaCollector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TaCollector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TaCollector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TaCollector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TaCollector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TaCollector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TaCollector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TaInput::Streamer(TBuffer &R__b)
{
   // Stream an object of class TaInput.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TaInput::Class(),this);
   } else {
      R__b.WriteClassBuffer(TaInput::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TaInput(void *p) {
      return  p ? new(p) ::TaInput : new ::TaInput;
   }
   static void *newArray_TaInput(Long_t nElements, void *p) {
      return p ? new(p) ::TaInput[nElements] : new ::TaInput[nElements];
   }
   // Wrapper around operator delete
   static void delete_TaInput(void *p) {
      delete ((::TaInput*)p);
   }
   static void deleteArray_TaInput(void *p) {
      delete [] ((::TaInput*)p);
   }
   static void destruct_TaInput(void *p) {
      typedef ::TaInput current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TaInput

//______________________________________________________________________________
void TaCollector::Streamer(TBuffer &R__b)
{
   // Stream an object of class TaCollector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TaCollector::Class(),this);
   } else {
      R__b.WriteClassBuffer(TaCollector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TaCollector(void *p) {
      return  p ? new(p) ::TaCollector : new ::TaCollector;
   }
   static void *newArray_TaCollector(Long_t nElements, void *p) {
      return p ? new(p) ::TaCollector[nElements] : new ::TaCollector[nElements];
   }
   // Wrapper around operator delete
   static void delete_TaCollector(void *p) {
      delete ((::TaCollector*)p);
   }
   static void deleteArray_TaCollector(void *p) {
      delete [] ((::TaCollector*)p);
   }
   static void destruct_TaCollector(void *p) {
      typedef ::TaCollector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TaCollector

namespace {
  void TriggerDictionaryInitialization_Collector_Dict_Impl() {
    static const char* headers[] = {
"TaInput.hh",
"TaCollector.hh",
0
    };
    static const char* includePaths[] = {
"/adaqfs/apps/ROOT/6.14-04/include",
"/adaqfs/apps/ROOT/6.14-04/include",
"/adaqfs/home/apar/PREX/prompt/collector/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "Collector_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TaInput.hh")))  TaInput;
class __attribute__((annotate("$clingAutoload$TaCollector.hh")))  TaCollector;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Collector_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TaInput.hh"
#include "TaCollector.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TaCollector", payloadCode, "@",
"TaInput", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Collector_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Collector_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Collector_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Collector_Dict() {
  TriggerDictionaryInitialization_Collector_Dict_Impl();
}
