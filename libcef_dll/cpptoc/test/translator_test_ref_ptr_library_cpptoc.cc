// Copyright (c) 2024 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=22ec6e9cbb7642581bff1c19a7f9a94b3278bdda$
//

#include "libcef_dll/cpptoc/test/translator_test_ref_ptr_library_cpptoc.h"

#include "libcef_dll/cpptoc/test/translator_test_ref_ptr_library_child_child_cpptoc.h"
#include "libcef_dll/cpptoc/test/translator_test_ref_ptr_library_child_cpptoc.h"
#include "libcef_dll/shutdown_checker.h"

// GLOBAL FUNCTIONS - Body may be edited by hand.

CEF_EXPORT cef_translator_test_ref_ptr_library_t*
cef_translator_test_ref_ptr_library_create(int value) {
  shutdown_checker::AssertNotShutdown();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  CefRefPtr<CefTranslatorTestRefPtrLibrary> _retval =
      CefTranslatorTestRefPtrLibrary::Create(value);

  // Return type: refptr_same
  return CefTranslatorTestRefPtrLibraryCppToC::Wrap(_retval);
}

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

int CEF_CALLBACK translator_test_ref_ptr_library_get_value(
    struct _cef_translator_test_ref_ptr_library_t* self) {
  shutdown_checker::AssertNotShutdown();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self) {
    return 0;
  }

  // Execute
  int _retval = CefTranslatorTestRefPtrLibraryCppToC::Get(self)->GetValue();

  // Return type: simple
  return _retval;
}

void CEF_CALLBACK translator_test_ref_ptr_library_set_value(
    struct _cef_translator_test_ref_ptr_library_t* self,
    int value) {
  shutdown_checker::AssertNotShutdown();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self) {
    return;
  }

  // Execute
  CefTranslatorTestRefPtrLibraryCppToC::Get(self)->SetValue(value);
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

CefTranslatorTestRefPtrLibraryCppToC::CefTranslatorTestRefPtrLibraryCppToC() {
  GetStruct()->get_value = translator_test_ref_ptr_library_get_value;
  GetStruct()->set_value = translator_test_ref_ptr_library_set_value;
}

// DESTRUCTOR - Do not edit by hand.

CefTranslatorTestRefPtrLibraryCppToC::~CefTranslatorTestRefPtrLibraryCppToC() {
  shutdown_checker::AssertNotShutdown();
}

template <>
CefRefPtr<CefTranslatorTestRefPtrLibrary>
CefCppToCRefCounted<CefTranslatorTestRefPtrLibraryCppToC,
                    CefTranslatorTestRefPtrLibrary,
                    cef_translator_test_ref_ptr_library_t>::
    UnwrapDerived(CefWrapperType type,
                  cef_translator_test_ref_ptr_library_t* s) {
  if (type == WT_TRANSLATOR_TEST_REF_PTR_LIBRARY_CHILD) {
    return CefTranslatorTestRefPtrLibraryChildCppToC::Unwrap(
        reinterpret_cast<cef_translator_test_ref_ptr_library_child_t*>(s));
  }
  if (type == WT_TRANSLATOR_TEST_REF_PTR_LIBRARY_CHILD_CHILD) {
    return CefTranslatorTestRefPtrLibraryChildChildCppToC::Unwrap(
        reinterpret_cast<cef_translator_test_ref_ptr_library_child_child_t*>(
            s));
  }
  DCHECK(false) << "Unexpected class type: " << type;
  return nullptr;
}

template <>
CefWrapperType
    CefCppToCRefCounted<CefTranslatorTestRefPtrLibraryCppToC,
                        CefTranslatorTestRefPtrLibrary,
                        cef_translator_test_ref_ptr_library_t>::kWrapperType =
        WT_TRANSLATOR_TEST_REF_PTR_LIBRARY;
