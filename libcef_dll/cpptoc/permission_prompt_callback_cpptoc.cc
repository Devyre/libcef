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
// $hash=dabee9d02c60280d0e87b1428999be9daa952681$
//

#include "libcef_dll/cpptoc/permission_prompt_callback_cpptoc.h"

#include "libcef_dll/shutdown_checker.h"

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

void CEF_CALLBACK
permission_prompt_callback_cont(struct _cef_permission_prompt_callback_t* self,
                                cef_permission_request_result_t result) {
  shutdown_checker::AssertNotShutdown();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self) {
    return;
  }

  // Execute
  CefPermissionPromptCallbackCppToC::Get(self)->Continue(result);
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

CefPermissionPromptCallbackCppToC::CefPermissionPromptCallbackCppToC() {
  GetStruct()->cont = permission_prompt_callback_cont;
}

// DESTRUCTOR - Do not edit by hand.

CefPermissionPromptCallbackCppToC::~CefPermissionPromptCallbackCppToC() {
  shutdown_checker::AssertNotShutdown();
}

template <>
CefRefPtr<CefPermissionPromptCallback>
CefCppToCRefCounted<CefPermissionPromptCallbackCppToC,
                    CefPermissionPromptCallback,
                    cef_permission_prompt_callback_t>::
    UnwrapDerived(CefWrapperType type, cef_permission_prompt_callback_t* s) {
  DCHECK(false) << "Unexpected class type: " << type;
  return nullptr;
}

template <>
CefWrapperType
    CefCppToCRefCounted<CefPermissionPromptCallbackCppToC,
                        CefPermissionPromptCallback,
                        cef_permission_prompt_callback_t>::kWrapperType =
        WT_PERMISSION_PROMPT_CALLBACK;
