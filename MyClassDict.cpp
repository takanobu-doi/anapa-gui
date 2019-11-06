// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME MyClassDict

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
#include "GroupBox.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_GroupBox(void *p = 0);
   static void *newArray_GroupBox(Long_t size, void *p);
   static void delete_GroupBox(void *p);
   static void deleteArray_GroupBox(void *p);
   static void destruct_GroupBox(void *p);
   static void streamer_GroupBox(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GroupBox*)
   {
      ::GroupBox *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GroupBox >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GroupBox", ::GroupBox::Class_Version(), "GroupBox.hpp", 23,
                  typeid(::GroupBox), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GroupBox::Dictionary, isa_proxy, 16,
                  sizeof(::GroupBox) );
      instance.SetNew(&new_GroupBox);
      instance.SetNewArray(&newArray_GroupBox);
      instance.SetDelete(&delete_GroupBox);
      instance.SetDeleteArray(&deleteArray_GroupBox);
      instance.SetDestructor(&destruct_GroupBox);
      instance.SetStreamerFunc(&streamer_GroupBox);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GroupBox*)
   {
      return GenerateInitInstanceLocal((::GroupBox*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GroupBox*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr GroupBox::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GroupBox::Class_Name()
{
   return "GroupBox";
}

//______________________________________________________________________________
const char *GroupBox::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GroupBox*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GroupBox::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GroupBox*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GroupBox::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GroupBox*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GroupBox::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GroupBox*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void GroupBox::Streamer(TBuffer &R__b)
{
   // Stream an object of class GroupBox.

   TGGroupFrame::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GroupBox(void *p) {
      return  p ? new(p) ::GroupBox : new ::GroupBox;
   }
   static void *newArray_GroupBox(Long_t nElements, void *p) {
      return p ? new(p) ::GroupBox[nElements] : new ::GroupBox[nElements];
   }
   // Wrapper around operator delete
   static void delete_GroupBox(void *p) {
      delete ((::GroupBox*)p);
   }
   static void deleteArray_GroupBox(void *p) {
      delete [] ((::GroupBox*)p);
   }
   static void destruct_GroupBox(void *p) {
      typedef ::GroupBox current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_GroupBox(TBuffer &buf, void *obj) {
      ((::GroupBox*)obj)->::GroupBox::Streamer(buf);
   }
} // end of namespace ROOT for class ::GroupBox

namespace {
  void TriggerDictionaryInitialization_MyClassDict_Impl() {
    static const char* headers[] = {
"GroupBox.hpp",
0
    };
    static const char* includePaths[] = {
"/home/takanobu/cern/root-6.14.04/obj/include",
"/hdd1/work1/master/anapa-gui/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "MyClassDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$GroupBox.hpp")))  GroupBox;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "MyClassDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "GroupBox.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"GroupBox", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("MyClassDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_MyClassDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_MyClassDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_MyClassDict() {
  TriggerDictionaryInitialization_MyClassDict_Impl();
}
