// Copyright 2015 The Chromium Embedded Framework Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <utility>

#include "base/memory/ptr_util.h"
#include "build/build_config.h"
#include "cef/libcef/browser/browser_host_base.h"
#include "cef/libcef/browser/browser_platform_delegate.h"
#include "cef/libcef/browser/chrome/browser_platform_delegate_chrome.h"
#include "cef/libcef/browser/chrome/views/browser_platform_delegate_chrome_child_window.h"
#include "cef/libcef/browser/chrome/views/browser_platform_delegate_chrome_views.h"
#include "cef/libcef/browser/chrome/views/chrome_child_window.h"
#include "cef/libcef/browser/context.h"
#include "cef/libcef/browser/views/browser_platform_delegate_views.h"

#if BUILDFLAG(IS_WIN)
#include "cef/libcef/browser/native/browser_platform_delegate_native_win.h"
#include "cef/libcef/browser/osr/browser_platform_delegate_osr_win.h"
#elif BUILDFLAG(IS_MAC)
#include "cef/libcef/browser/native/browser_platform_delegate_native_mac.h"
#include "cef/libcef/browser/osr/browser_platform_delegate_osr_mac.h"
#elif BUILDFLAG(IS_LINUX)
#include "cef/libcef/browser/native/browser_platform_delegate_native_linux.h"
#include "cef/libcef/browser/osr/browser_platform_delegate_osr_linux.h"
#else
#error A delegate implementation is not available for your platform.
#endif

#if BUILDFLAG(ENABLE_ALLOY_BOOTSTRAP)
#include "cef/libcef/browser/extensions/browser_platform_delegate_background.h"
#endif

namespace {

std::unique_ptr<CefBrowserPlatformDelegateNative> CreateNativeDelegate(
    const CefWindowInfo& window_info,
    SkColor background_color) {
#if BUILDFLAG(IS_WIN)
  return std::make_unique<CefBrowserPlatformDelegateNativeWin>(
      window_info, background_color);
#elif BUILDFLAG(IS_MAC)
  return std::make_unique<CefBrowserPlatformDelegateNativeMac>(
      window_info, background_color);
#elif BUILDFLAG(IS_LINUX)
  return std::make_unique<CefBrowserPlatformDelegateNativeLinux>(
      window_info, background_color);
#endif
}

std::unique_ptr<CefBrowserPlatformDelegateOsr> CreateOSRDelegate(
    std::unique_ptr<CefBrowserPlatformDelegateNative> native_delegate,
    bool use_shared_texture,
    bool use_external_begin_frame) {
#if BUILDFLAG(IS_WIN)
  return std::make_unique<CefBrowserPlatformDelegateOsrWin>(
      std::move(native_delegate), use_shared_texture, use_external_begin_frame);
#elif BUILDFLAG(IS_MAC)
  return std::make_unique<CefBrowserPlatformDelegateOsrMac>(
      std::move(native_delegate), use_shared_texture, use_external_begin_frame);
#elif BUILDFLAG(IS_LINUX)
  return std::make_unique<CefBrowserPlatformDelegateOsrLinux>(
      std::move(native_delegate), use_shared_texture, use_external_begin_frame);
#endif
}

}  // namespace

// static
std::unique_ptr<CefBrowserPlatformDelegate> CefBrowserPlatformDelegate::Create(
    const CefBrowserCreateParams& create_params) {
  const bool is_windowless = create_params.IsWindowless();
  const SkColor background_color = CefContext::Get()->GetBackgroundColor(
      &create_params.settings, is_windowless ? STATE_ENABLED : STATE_DISABLED);

  if (create_params.IsChromeStyle()) {
    CefWindowInfo window_info;
    if (create_params.window_info) {
      window_info = *create_params.window_info;
    }

    std::unique_ptr<CefBrowserPlatformDelegateNative> native_delegate =
        CreateNativeDelegate(window_info, background_color);

    if (create_params.window_info) {
      // CefWindowInfo should only be set if a parent handle was specified.
      DCHECK(chrome_child_window::HasParentHandle(window_info));
      return std::make_unique<CefBrowserPlatformDelegateChromeChildWindow>(
          std::move(native_delegate),
          static_cast<CefBrowserViewImpl*>(create_params.browser_view.get()));
    } else if (create_params.browser_view ||
               create_params.popup_with_views_hosted_opener) {
      // CefWindowInfo is not used in this case.
      return std::make_unique<CefBrowserPlatformDelegateChromeViews>(
          std::move(native_delegate),
          static_cast<CefBrowserViewImpl*>(create_params.browser_view.get()));
    }

    return std::make_unique<CefBrowserPlatformDelegateChrome>(
        std::move(native_delegate));
  }

  if (create_params.browser_view ||
      create_params.popup_with_views_hosted_opener) {
    // CefWindowInfo is not used in this case.
    std::unique_ptr<CefBrowserPlatformDelegateNative> native_delegate =
        CreateNativeDelegate(CefWindowInfo(), background_color);
    return std::make_unique<CefBrowserPlatformDelegateViews>(
        std::move(native_delegate),
        static_cast<CefBrowserViewImpl*>(create_params.browser_view.get()));
#if BUILDFLAG(ENABLE_ALLOY_BOOTSTRAP)
  } else if (create_params.extension_host_type ==
             extensions::mojom::ViewType::kExtensionBackgroundPage) {
    // Creating a background extension host without a window.
    std::unique_ptr<CefBrowserPlatformDelegateNative> native_delegate =
        CreateNativeDelegate(CefWindowInfo(), background_color);
    return std::make_unique<CefBrowserPlatformDelegateBackground>(
        std::move(native_delegate));
#endif
  } else if (create_params.window_info) {
    std::unique_ptr<CefBrowserPlatformDelegateNative> native_delegate =
        CreateNativeDelegate(*create_params.window_info, background_color);
    if (is_windowless) {
      const bool use_shared_texture =
          create_params.window_info->shared_texture_enabled;

      const bool use_external_begin_frame =
          create_params.window_info->external_begin_frame_enabled;

      return CreateOSRDelegate(std::move(native_delegate), use_shared_texture,
                               use_external_begin_frame);
    }
    return std::move(native_delegate);
  }

  DCHECK(false);
  return nullptr;
}
