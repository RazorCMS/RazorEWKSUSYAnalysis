// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME rootdict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
#include "CustomPdfs.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_RooCB(void *p = 0);
   static void *newArray_RooCB(Long_t size, void *p);
   static void delete_RooCB(void *p);
   static void deleteArray_RooCB(void *p);
   static void destruct_RooCB(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooCB*)
   {
      ::RooCB *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooCB >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooCB", ::RooCB::Class_Version(), "CustomPdfs.hh", 8,
                  typeid(::RooCB), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooCB::Dictionary, isa_proxy, 4,
                  sizeof(::RooCB) );
      instance.SetNew(&new_RooCB);
      instance.SetNewArray(&newArray_RooCB);
      instance.SetDelete(&delete_RooCB);
      instance.SetDeleteArray(&deleteArray_RooCB);
      instance.SetDestructor(&destruct_RooCB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooCB*)
   {
      return GenerateInitInstanceLocal((::RooCB*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooCB*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooHMDiphoton(void *p = 0);
   static void *newArray_RooHMDiphoton(Long_t size, void *p);
   static void delete_RooHMDiphoton(void *p);
   static void deleteArray_RooHMDiphoton(void *p);
   static void destruct_RooHMDiphoton(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooHMDiphoton*)
   {
      ::RooHMDiphoton *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooHMDiphoton >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooHMDiphoton", ::RooHMDiphoton::Class_Version(), "CustomPdfs.hh", 39,
                  typeid(::RooHMDiphoton), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooHMDiphoton::Dictionary, isa_proxy, 4,
                  sizeof(::RooHMDiphoton) );
      instance.SetNew(&new_RooHMDiphoton);
      instance.SetNewArray(&newArray_RooHMDiphoton);
      instance.SetDelete(&delete_RooHMDiphoton);
      instance.SetDeleteArray(&deleteArray_RooHMDiphoton);
      instance.SetDestructor(&destruct_RooHMDiphoton);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooHMDiphoton*)
   {
      return GenerateInitInstanceLocal((::RooHMDiphoton*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooHMDiphoton*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooDoubleCB(void *p = 0);
   static void *newArray_RooDoubleCB(Long_t size, void *p);
   static void delete_RooDoubleCB(void *p);
   static void deleteArray_RooDoubleCB(void *p);
   static void destruct_RooDoubleCB(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooDoubleCB*)
   {
      ::RooDoubleCB *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooDoubleCB >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooDoubleCB", ::RooDoubleCB::Class_Version(), "CustomPdfs.hh", 64,
                  typeid(::RooDoubleCB), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooDoubleCB::Dictionary, isa_proxy, 4,
                  sizeof(::RooDoubleCB) );
      instance.SetNew(&new_RooDoubleCB);
      instance.SetNewArray(&newArray_RooDoubleCB);
      instance.SetDelete(&delete_RooDoubleCB);
      instance.SetDeleteArray(&deleteArray_RooDoubleCB);
      instance.SetDestructor(&destruct_RooDoubleCB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooDoubleCB*)
   {
      return GenerateInitInstanceLocal((::RooDoubleCB*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooDoubleCB*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooFermi(void *p = 0);
   static void *newArray_RooFermi(Long_t size, void *p);
   static void delete_RooFermi(void *p);
   static void deleteArray_RooFermi(void *p);
   static void destruct_RooFermi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooFermi*)
   {
      ::RooFermi *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooFermi >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooFermi", ::RooFermi::Class_Version(), "CustomPdfs.hh", 200,
                  typeid(::RooFermi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooFermi::Dictionary, isa_proxy, 4,
                  sizeof(::RooFermi) );
      instance.SetNew(&new_RooFermi);
      instance.SetNewArray(&newArray_RooFermi);
      instance.SetDelete(&delete_RooFermi);
      instance.SetDeleteArray(&deleteArray_RooFermi);
      instance.SetDestructor(&destruct_RooFermi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooFermi*)
   {
      return GenerateInitInstanceLocal((::RooFermi*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooFermi*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooRelBW(void *p = 0);
   static void *newArray_RooRelBW(Long_t size, void *p);
   static void delete_RooRelBW(void *p);
   static void deleteArray_RooRelBW(void *p);
   static void destruct_RooRelBW(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooRelBW*)
   {
      ::RooRelBW *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooRelBW >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooRelBW", ::RooRelBW::Class_Version(), "CustomPdfs.hh", 225,
                  typeid(::RooRelBW), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooRelBW::Dictionary, isa_proxy, 4,
                  sizeof(::RooRelBW) );
      instance.SetNew(&new_RooRelBW);
      instance.SetNewArray(&newArray_RooRelBW);
      instance.SetDelete(&delete_RooRelBW);
      instance.SetDeleteArray(&deleteArray_RooRelBW);
      instance.SetDestructor(&destruct_RooRelBW);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooRelBW*)
   {
      return GenerateInitInstanceLocal((::RooRelBW*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooRelBW*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Triangle(void *p = 0);
   static void *newArray_Triangle(Long_t size, void *p);
   static void delete_Triangle(void *p);
   static void deleteArray_Triangle(void *p);
   static void destruct_Triangle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Triangle*)
   {
      ::Triangle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Triangle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Triangle", ::Triangle::Class_Version(), "CustomPdfs.hh", 253,
                  typeid(::Triangle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Triangle::Dictionary, isa_proxy, 4,
                  sizeof(::Triangle) );
      instance.SetNew(&new_Triangle);
      instance.SetNewArray(&newArray_Triangle);
      instance.SetDelete(&delete_Triangle);
      instance.SetDeleteArray(&deleteArray_Triangle);
      instance.SetDestructor(&destruct_Triangle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Triangle*)
   {
      return GenerateInitInstanceLocal((::Triangle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Triangle*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooLevelledExp(void *p = 0);
   static void *newArray_RooLevelledExp(Long_t size, void *p);
   static void delete_RooLevelledExp(void *p);
   static void deleteArray_RooLevelledExp(void *p);
   static void destruct_RooLevelledExp(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooLevelledExp*)
   {
      ::RooLevelledExp *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooLevelledExp >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooLevelledExp", ::RooLevelledExp::Class_Version(), "CustomPdfs.hh", 286,
                  typeid(::RooLevelledExp), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooLevelledExp::Dictionary, isa_proxy, 4,
                  sizeof(::RooLevelledExp) );
      instance.SetNew(&new_RooLevelledExp);
      instance.SetNewArray(&newArray_RooLevelledExp);
      instance.SetDelete(&delete_RooLevelledExp);
      instance.SetDeleteArray(&deleteArray_RooLevelledExp);
      instance.SetDestructor(&destruct_RooLevelledExp);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooLevelledExp*)
   {
      return GenerateInitInstanceLocal((::RooLevelledExp*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooLevelledExp*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooDoubleCBInterpolate(void *p = 0);
   static void *newArray_RooDoubleCBInterpolate(Long_t size, void *p);
   static void delete_RooDoubleCBInterpolate(void *p);
   static void deleteArray_RooDoubleCBInterpolate(void *p);
   static void destruct_RooDoubleCBInterpolate(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooDoubleCBInterpolate*)
   {
      ::RooDoubleCBInterpolate *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooDoubleCBInterpolate >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooDoubleCBInterpolate", ::RooDoubleCBInterpolate::Class_Version(), "CustomPdfs.hh", 100,
                  typeid(::RooDoubleCBInterpolate), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooDoubleCBInterpolate::Dictionary, isa_proxy, 4,
                  sizeof(::RooDoubleCBInterpolate) );
      instance.SetNew(&new_RooDoubleCBInterpolate);
      instance.SetNewArray(&newArray_RooDoubleCBInterpolate);
      instance.SetDelete(&delete_RooDoubleCBInterpolate);
      instance.SetDeleteArray(&deleteArray_RooDoubleCBInterpolate);
      instance.SetDestructor(&destruct_RooDoubleCBInterpolate);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooDoubleCBInterpolate*)
   {
      return GenerateInitInstanceLocal((::RooDoubleCBInterpolate*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooDoubleCBInterpolate*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooIntepolateDSCB_W0p014_Spin0_EBEB(void *p = 0);
   static void *newArray_RooIntepolateDSCB_W0p014_Spin0_EBEB(Long_t size, void *p);
   static void delete_RooIntepolateDSCB_W0p014_Spin0_EBEB(void *p);
   static void deleteArray_RooIntepolateDSCB_W0p014_Spin0_EBEB(void *p);
   static void destruct_RooIntepolateDSCB_W0p014_Spin0_EBEB(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooIntepolateDSCB_W0p014_Spin0_EBEB*)
   {
      ::RooIntepolateDSCB_W0p014_Spin0_EBEB *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooIntepolateDSCB_W0p014_Spin0_EBEB >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooIntepolateDSCB_W0p014_Spin0_EBEB", ::RooIntepolateDSCB_W0p014_Spin0_EBEB::Class_Version(), "CustomPdfs.hh", 134,
                  typeid(::RooIntepolateDSCB_W0p014_Spin0_EBEB), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooIntepolateDSCB_W0p014_Spin0_EBEB::Dictionary, isa_proxy, 4,
                  sizeof(::RooIntepolateDSCB_W0p014_Spin0_EBEB) );
      instance.SetNew(&new_RooIntepolateDSCB_W0p014_Spin0_EBEB);
      instance.SetNewArray(&newArray_RooIntepolateDSCB_W0p014_Spin0_EBEB);
      instance.SetDelete(&delete_RooIntepolateDSCB_W0p014_Spin0_EBEB);
      instance.SetDeleteArray(&deleteArray_RooIntepolateDSCB_W0p014_Spin0_EBEB);
      instance.SetDestructor(&destruct_RooIntepolateDSCB_W0p014_Spin0_EBEB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooIntepolateDSCB_W0p014_Spin0_EBEB*)
   {
      return GenerateInitInstanceLocal((::RooIntepolateDSCB_W0p014_Spin0_EBEB*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooIntepolateDSCB_W0p014_Spin0_EBEB*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooIntepolateDSCB_W0p014_Spin0_EBEE(void *p = 0);
   static void *newArray_RooIntepolateDSCB_W0p014_Spin0_EBEE(Long_t size, void *p);
   static void delete_RooIntepolateDSCB_W0p014_Spin0_EBEE(void *p);
   static void deleteArray_RooIntepolateDSCB_W0p014_Spin0_EBEE(void *p);
   static void destruct_RooIntepolateDSCB_W0p014_Spin0_EBEE(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooIntepolateDSCB_W0p014_Spin0_EBEE*)
   {
      ::RooIntepolateDSCB_W0p014_Spin0_EBEE *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooIntepolateDSCB_W0p014_Spin0_EBEE >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooIntepolateDSCB_W0p014_Spin0_EBEE", ::RooIntepolateDSCB_W0p014_Spin0_EBEE::Class_Version(), "CustomPdfs.hh", 167,
                  typeid(::RooIntepolateDSCB_W0p014_Spin0_EBEE), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooIntepolateDSCB_W0p014_Spin0_EBEE::Dictionary, isa_proxy, 4,
                  sizeof(::RooIntepolateDSCB_W0p014_Spin0_EBEE) );
      instance.SetNew(&new_RooIntepolateDSCB_W0p014_Spin0_EBEE);
      instance.SetNewArray(&newArray_RooIntepolateDSCB_W0p014_Spin0_EBEE);
      instance.SetDelete(&delete_RooIntepolateDSCB_W0p014_Spin0_EBEE);
      instance.SetDeleteArray(&deleteArray_RooIntepolateDSCB_W0p014_Spin0_EBEE);
      instance.SetDestructor(&destruct_RooIntepolateDSCB_W0p014_Spin0_EBEE);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooIntepolateDSCB_W0p014_Spin0_EBEE*)
   {
      return GenerateInitInstanceLocal((::RooIntepolateDSCB_W0p014_Spin0_EBEE*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooIntepolateDSCB_W0p014_Spin0_EBEE*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr RooCB::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooCB::Class_Name()
{
   return "RooCB";
}

//______________________________________________________________________________
const char *RooCB::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooCB*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooCB::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooCB*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooCB::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooCB*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooCB::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooCB*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooHMDiphoton::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooHMDiphoton::Class_Name()
{
   return "RooHMDiphoton";
}

//______________________________________________________________________________
const char *RooHMDiphoton::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooHMDiphoton*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooHMDiphoton::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooHMDiphoton*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooHMDiphoton::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooHMDiphoton*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooHMDiphoton::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooHMDiphoton*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooDoubleCB::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooDoubleCB::Class_Name()
{
   return "RooDoubleCB";
}

//______________________________________________________________________________
const char *RooDoubleCB::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCB*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooDoubleCB::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCB*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooDoubleCB::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCB*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooDoubleCB::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCB*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooFermi::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooFermi::Class_Name()
{
   return "RooFermi";
}

//______________________________________________________________________________
const char *RooFermi::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooFermi*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooFermi::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooFermi*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooFermi::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooFermi*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooFermi::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooFermi*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooRelBW::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooRelBW::Class_Name()
{
   return "RooRelBW";
}

//______________________________________________________________________________
const char *RooRelBW::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooRelBW*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooRelBW::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooRelBW*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooRelBW::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooRelBW*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooRelBW::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooRelBW*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Triangle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Triangle::Class_Name()
{
   return "Triangle";
}

//______________________________________________________________________________
const char *Triangle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Triangle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Triangle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Triangle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Triangle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Triangle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Triangle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Triangle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooLevelledExp::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooLevelledExp::Class_Name()
{
   return "RooLevelledExp";
}

//______________________________________________________________________________
const char *RooLevelledExp::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooLevelledExp*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooLevelledExp::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooLevelledExp*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooLevelledExp::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooLevelledExp*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooLevelledExp::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooLevelledExp*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooDoubleCBInterpolate::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooDoubleCBInterpolate::Class_Name()
{
   return "RooDoubleCBInterpolate";
}

//______________________________________________________________________________
const char *RooDoubleCBInterpolate::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCBInterpolate*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooDoubleCBInterpolate::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCBInterpolate*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooDoubleCBInterpolate::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCBInterpolate*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooDoubleCBInterpolate::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooDoubleCBInterpolate*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooIntepolateDSCB_W0p014_Spin0_EBEB::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooIntepolateDSCB_W0p014_Spin0_EBEB::Class_Name()
{
   return "RooIntepolateDSCB_W0p014_Spin0_EBEB";
}

//______________________________________________________________________________
const char *RooIntepolateDSCB_W0p014_Spin0_EBEB::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooIntepolateDSCB_W0p014_Spin0_EBEB*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooIntepolateDSCB_W0p014_Spin0_EBEB::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooIntepolateDSCB_W0p014_Spin0_EBEB*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooIntepolateDSCB_W0p014_Spin0_EBEB::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooIntepolateDSCB_W0p014_Spin0_EBEB*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooIntepolateDSCB_W0p014_Spin0_EBEB::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooIntepolateDSCB_W0p014_Spin0_EBEB*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooIntepolateDSCB_W0p014_Spin0_EBEE::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooIntepolateDSCB_W0p014_Spin0_EBEE::Class_Name()
{
   return "RooIntepolateDSCB_W0p014_Spin0_EBEE";
}

//______________________________________________________________________________
const char *RooIntepolateDSCB_W0p014_Spin0_EBEE::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooIntepolateDSCB_W0p014_Spin0_EBEE*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooIntepolateDSCB_W0p014_Spin0_EBEE::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooIntepolateDSCB_W0p014_Spin0_EBEE*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooIntepolateDSCB_W0p014_Spin0_EBEE::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooIntepolateDSCB_W0p014_Spin0_EBEE*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooIntepolateDSCB_W0p014_Spin0_EBEE::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooIntepolateDSCB_W0p014_Spin0_EBEE*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void RooCB::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooCB.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooCB::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooCB::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooCB(void *p) {
      return  p ? new(p) ::RooCB : new ::RooCB;
   }
   static void *newArray_RooCB(Long_t nElements, void *p) {
      return p ? new(p) ::RooCB[nElements] : new ::RooCB[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooCB(void *p) {
      delete ((::RooCB*)p);
   }
   static void deleteArray_RooCB(void *p) {
      delete [] ((::RooCB*)p);
   }
   static void destruct_RooCB(void *p) {
      typedef ::RooCB current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RooCB

//______________________________________________________________________________
void RooHMDiphoton::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooHMDiphoton.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooHMDiphoton::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooHMDiphoton::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooHMDiphoton(void *p) {
      return  p ? new(p) ::RooHMDiphoton : new ::RooHMDiphoton;
   }
   static void *newArray_RooHMDiphoton(Long_t nElements, void *p) {
      return p ? new(p) ::RooHMDiphoton[nElements] : new ::RooHMDiphoton[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooHMDiphoton(void *p) {
      delete ((::RooHMDiphoton*)p);
   }
   static void deleteArray_RooHMDiphoton(void *p) {
      delete [] ((::RooHMDiphoton*)p);
   }
   static void destruct_RooHMDiphoton(void *p) {
      typedef ::RooHMDiphoton current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RooHMDiphoton

//______________________________________________________________________________
void RooDoubleCB::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooDoubleCB.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooDoubleCB::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooDoubleCB::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooDoubleCB(void *p) {
      return  p ? new(p) ::RooDoubleCB : new ::RooDoubleCB;
   }
   static void *newArray_RooDoubleCB(Long_t nElements, void *p) {
      return p ? new(p) ::RooDoubleCB[nElements] : new ::RooDoubleCB[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooDoubleCB(void *p) {
      delete ((::RooDoubleCB*)p);
   }
   static void deleteArray_RooDoubleCB(void *p) {
      delete [] ((::RooDoubleCB*)p);
   }
   static void destruct_RooDoubleCB(void *p) {
      typedef ::RooDoubleCB current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RooDoubleCB

//______________________________________________________________________________
void RooFermi::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooFermi.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooFermi::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooFermi::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooFermi(void *p) {
      return  p ? new(p) ::RooFermi : new ::RooFermi;
   }
   static void *newArray_RooFermi(Long_t nElements, void *p) {
      return p ? new(p) ::RooFermi[nElements] : new ::RooFermi[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooFermi(void *p) {
      delete ((::RooFermi*)p);
   }
   static void deleteArray_RooFermi(void *p) {
      delete [] ((::RooFermi*)p);
   }
   static void destruct_RooFermi(void *p) {
      typedef ::RooFermi current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RooFermi

//______________________________________________________________________________
void RooRelBW::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooRelBW.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooRelBW::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooRelBW::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooRelBW(void *p) {
      return  p ? new(p) ::RooRelBW : new ::RooRelBW;
   }
   static void *newArray_RooRelBW(Long_t nElements, void *p) {
      return p ? new(p) ::RooRelBW[nElements] : new ::RooRelBW[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooRelBW(void *p) {
      delete ((::RooRelBW*)p);
   }
   static void deleteArray_RooRelBW(void *p) {
      delete [] ((::RooRelBW*)p);
   }
   static void destruct_RooRelBW(void *p) {
      typedef ::RooRelBW current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RooRelBW

//______________________________________________________________________________
void Triangle::Streamer(TBuffer &R__b)
{
   // Stream an object of class Triangle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Triangle::Class(),this);
   } else {
      R__b.WriteClassBuffer(Triangle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Triangle(void *p) {
      return  p ? new(p) ::Triangle : new ::Triangle;
   }
   static void *newArray_Triangle(Long_t nElements, void *p) {
      return p ? new(p) ::Triangle[nElements] : new ::Triangle[nElements];
   }
   // Wrapper around operator delete
   static void delete_Triangle(void *p) {
      delete ((::Triangle*)p);
   }
   static void deleteArray_Triangle(void *p) {
      delete [] ((::Triangle*)p);
   }
   static void destruct_Triangle(void *p) {
      typedef ::Triangle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Triangle

//______________________________________________________________________________
void RooLevelledExp::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooLevelledExp.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooLevelledExp::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooLevelledExp::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooLevelledExp(void *p) {
      return  p ? new(p) ::RooLevelledExp : new ::RooLevelledExp;
   }
   static void *newArray_RooLevelledExp(Long_t nElements, void *p) {
      return p ? new(p) ::RooLevelledExp[nElements] : new ::RooLevelledExp[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooLevelledExp(void *p) {
      delete ((::RooLevelledExp*)p);
   }
   static void deleteArray_RooLevelledExp(void *p) {
      delete [] ((::RooLevelledExp*)p);
   }
   static void destruct_RooLevelledExp(void *p) {
      typedef ::RooLevelledExp current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RooLevelledExp

//______________________________________________________________________________
void RooDoubleCBInterpolate::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooDoubleCBInterpolate.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooDoubleCBInterpolate::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooDoubleCBInterpolate::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooDoubleCBInterpolate(void *p) {
      return  p ? new(p) ::RooDoubleCBInterpolate : new ::RooDoubleCBInterpolate;
   }
   static void *newArray_RooDoubleCBInterpolate(Long_t nElements, void *p) {
      return p ? new(p) ::RooDoubleCBInterpolate[nElements] : new ::RooDoubleCBInterpolate[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooDoubleCBInterpolate(void *p) {
      delete ((::RooDoubleCBInterpolate*)p);
   }
   static void deleteArray_RooDoubleCBInterpolate(void *p) {
      delete [] ((::RooDoubleCBInterpolate*)p);
   }
   static void destruct_RooDoubleCBInterpolate(void *p) {
      typedef ::RooDoubleCBInterpolate current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RooDoubleCBInterpolate

//______________________________________________________________________________
void RooIntepolateDSCB_W0p014_Spin0_EBEB::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooIntepolateDSCB_W0p014_Spin0_EBEB.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooIntepolateDSCB_W0p014_Spin0_EBEB::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooIntepolateDSCB_W0p014_Spin0_EBEB::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooIntepolateDSCB_W0p014_Spin0_EBEB(void *p) {
      return  p ? new(p) ::RooIntepolateDSCB_W0p014_Spin0_EBEB : new ::RooIntepolateDSCB_W0p014_Spin0_EBEB;
   }
   static void *newArray_RooIntepolateDSCB_W0p014_Spin0_EBEB(Long_t nElements, void *p) {
      return p ? new(p) ::RooIntepolateDSCB_W0p014_Spin0_EBEB[nElements] : new ::RooIntepolateDSCB_W0p014_Spin0_EBEB[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooIntepolateDSCB_W0p014_Spin0_EBEB(void *p) {
      delete ((::RooIntepolateDSCB_W0p014_Spin0_EBEB*)p);
   }
   static void deleteArray_RooIntepolateDSCB_W0p014_Spin0_EBEB(void *p) {
      delete [] ((::RooIntepolateDSCB_W0p014_Spin0_EBEB*)p);
   }
   static void destruct_RooIntepolateDSCB_W0p014_Spin0_EBEB(void *p) {
      typedef ::RooIntepolateDSCB_W0p014_Spin0_EBEB current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RooIntepolateDSCB_W0p014_Spin0_EBEB

//______________________________________________________________________________
void RooIntepolateDSCB_W0p014_Spin0_EBEE::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooIntepolateDSCB_W0p014_Spin0_EBEE.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooIntepolateDSCB_W0p014_Spin0_EBEE::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooIntepolateDSCB_W0p014_Spin0_EBEE::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooIntepolateDSCB_W0p014_Spin0_EBEE(void *p) {
      return  p ? new(p) ::RooIntepolateDSCB_W0p014_Spin0_EBEE : new ::RooIntepolateDSCB_W0p014_Spin0_EBEE;
   }
   static void *newArray_RooIntepolateDSCB_W0p014_Spin0_EBEE(Long_t nElements, void *p) {
      return p ? new(p) ::RooIntepolateDSCB_W0p014_Spin0_EBEE[nElements] : new ::RooIntepolateDSCB_W0p014_Spin0_EBEE[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooIntepolateDSCB_W0p014_Spin0_EBEE(void *p) {
      delete ((::RooIntepolateDSCB_W0p014_Spin0_EBEE*)p);
   }
   static void deleteArray_RooIntepolateDSCB_W0p014_Spin0_EBEE(void *p) {
      delete [] ((::RooIntepolateDSCB_W0p014_Spin0_EBEE*)p);
   }
   static void destruct_RooIntepolateDSCB_W0p014_Spin0_EBEE(void *p) {
      typedef ::RooIntepolateDSCB_W0p014_Spin0_EBEE current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::RooIntepolateDSCB_W0p014_Spin0_EBEE

namespace {
  void TriggerDictionaryInitialization_rootdict_Impl() {
    static const char* headers[] = {
"CustomPdfs.hh",
0
    };
    static const char* includePaths[] = {
"/Users/cmorgoth/Work/git/RazorEWKSUSYAnalysis/HggRazor/FitMgg/include",
"/Users/cmorgoth/Downloads/MyRoot-6.06.02/include",
"/Users/cmorgoth/Work/git/RazorEWKSUSYAnalysis/HggRazor/FitMgg/include/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "rootdict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooCB;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooHMDiphoton;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooDoubleCB;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooFermi;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooRelBW;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  Triangle;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooLevelledExp;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooDoubleCBInterpolate;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooIntepolateDSCB_W0p014_Spin0_EBEB;
class __attribute__((annotate("$clingAutoload$CustomPdfs.hh")))  RooIntepolateDSCB_W0p014_Spin0_EBEE;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "rootdict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "CustomPdfs.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"RooCB", payloadCode, "@",
"RooDoubleCB", payloadCode, "@",
"RooDoubleCBInterpolate", payloadCode, "@",
"RooFermi", payloadCode, "@",
"RooHMDiphoton", payloadCode, "@",
"RooIntepolateDSCB_W0p014_Spin0_EBEB", payloadCode, "@",
"RooIntepolateDSCB_W0p014_Spin0_EBEE", payloadCode, "@",
"RooLevelledExp", payloadCode, "@",
"RooRelBW", payloadCode, "@",
"Triangle", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("rootdict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_rootdict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_rootdict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_rootdict() {
  TriggerDictionaryInitialization_rootdict_Impl();
}
