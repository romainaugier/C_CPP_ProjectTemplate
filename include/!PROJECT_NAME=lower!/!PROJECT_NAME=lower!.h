// SPDX-License-Identifier: BSD-3-Clause 
// Copyright (c) !YEAR! - Present !AUTHOR!
// All rights reserved. 

#pragma once

#if !defined(__!PROJECT_NAME:upper!)
#define __!PROJECT_NAME:upper!

#if defined(_MSC_VER)
#define !PROJECT_NAME:upper!_MSVC
#pragma warning(disable:4711) /* function selected for automatic inline expansion */
#define _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
#elif defined(__GNUC__)
#define !PROJECT_NAME:upper!_GCC
#elif defined(__clang__)
#define !PROJECT_NAME:upper!_CLANG
#endif /* defined(_MSC_VER) */

#define !PROJECT_NAME:upper!_STRIFY(x) #x
#define !PROJECT_NAME:upper!_STRIFY_MACRO(m) !PROJECT_NAME:upper!_STRIFY(m)

#if !defined(!PROJECT_NAME:upper!_VERSION_MAJOR)
#define !PROJECT_NAME:upper!_VERSION_MAJOR 0
#endif /* !defined(!PROJECT_NAME:upper!_VERSION_MAJOR) */

#if !defined(!PROJECT_NAME:upper!_VERSION_MINOR)
#define !PROJECT_NAME:upper!_VERSION_MINOR 0
#endif /* !defined(!PROJECT_NAME:upper!_VERSION_MINOR) */

#if !defined(!PROJECT_NAME:upper!_VERSION_PATCH)
#define !PROJECT_NAME:upper!_VERSION_PATCH 0
#endif /* !defined(!PROJECT_NAME:upper!_VERSION_PATCH) */

#if !defined(!PROJECT_NAME:upper!_VERSION_REVISION)
#define !PROJECT_NAME:upper!_VERSION_REVISION 0
#endif /* !defined(!PROJECT_NAME:upper!_VERSION_REVISION) */

#define !PROJECT_NAME:upper!_VERSION_STR !PROJECT_NAME:upper!_STRIFY_MACRO(!PROJECT_NAME:upper!_VERSION_MAJOR)"." \
                              !PROJECT_NAME:upper!_STRIFY_MACRO(!PROJECT_NAME:upper!_VERSION_MINOR)"." \
                              !PROJECT_NAME:upper!_STRIFY_MACRO(!PROJECT_NAME:upper!_VERSION_PATCH)"." \
                              !PROJECT_NAME:upper!_STRIFY_MACRO(!PROJECT_NAME:upper!_VERSION_REVISION)

#include <cstddef>
#include <cstdint>
#include <cassert>

#if INTPTR_MAX == INT64_MAX || defined(__x86_64__)
#define !PROJECT_NAME:upper!_X64
#define !PROJECT_NAME:upper!_SIZEOF_PTR 8
#elif INTPTR_MAX == INT32_MAX
#define !PROJECT_NAME:upper!_X86
#define !PROJECT_NAME:upper!_SIZEOF_PTR 4
#endif /* INTPTR_MAX == INT64_MAX || defined(__x86_64__) */

#if defined(_WIN32)
#define !PROJECT_NAME:upper!_WIN
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif /* !defined(WIN32_LEAN_AND_MEAN) */
#if defined(!PROJECT_NAME:upper!_X64)
#define !PROJECT_NAME:upper!_PLATFORM_STR "WIN64"
#else
#define !PROJECT_NAME:upper!_PLATFORM_STR "WIN32"
#endif /* defined(!PROJECT_NAME:upper!_x64) */
#elif defined(__linux__)
#define !PROJECT_NAME:upper!_LINUX
#if defined(!PROJECT_NAME:upper!_X64)
#define !PROJECT_NAME:upper!_PLATFORM_STR "LINUX64"
#else
#define !PROJECT_NAME:upper!_PLATFORM_STR "LINUX32"
#endif /* defined(!PROJECT_NAME:upper!_X64) */
#endif /* defined(_WIN32) */

#if defined(!PROJECT_NAME:upper!_WIN)
#if defined(!PROJECT_NAME:upper!_MSVC)
#define !PROJECT_NAME:upper!_EXPORT __declspec(dllexport)
#define !PROJECT_NAME:upper!_IMPORT __declspec(dllimport)
#elif defined(!PROJECT_NAME:upper!_GCC) || defined(!PROJECT_NAME:upper!_CLANG)
#define !PROJECT_NAME:upper!_EXPORT __attribute__((dllexport))
#define !PROJECT_NAME:upper!_IMPORT __attribute__((dllimport))
#endif /* defined(!PROJECT_NAME:upper!_MSVC) */
#elif defined(!PROJECT_NAME:upper!_LINUX)
#define !PROJECT_NAME:upper!_EXPORT __attribute__((visibility("default")))
#define !PROJECT_NAME:upper!_IMPORT
#endif /* defined(!PROJECT_NAME:upper!_WIN) */

#if defined(!PROJECT_NAME:upper!_MSVC)
#define !PROJECT_NAME:upper!_FORCE_INLINE __forceinline
#define !PROJECT_NAME:upper!_LIB_ENTRY
#define !PROJECT_NAME:upper!_LIB_EXIT
#elif defined(!PROJECT_NAME:upper!_GCC)
#define !PROJECT_NAME:upper!_FORCE_INLINE inline __attribute__((always_inline)) 
#define !PROJECT_NAME:upper!_LIB_ENTRY __attribute__((constructor))
#define !PROJECT_NAME:upper!_LIB_EXIT __attribute__((destructor))
#elif defined(!PROJECT_NAME:upper!_CLANG)
#define !PROJECT_NAME:upper!_FORCE_INLINE __attribute__((always_inline))
#define !PROJECT_NAME:upper!_LIB_ENTRY __attribute__((constructor))
#define !PROJECT_NAME:upper!_LIB_EXIT __attribute__((destructor))
#endif /* defined(!PROJECT_NAME:upper!_MSVC) */

#if defined(!PROJECT_NAME:upper!_BUILD_SHARED)
#define !PROJECT_NAME:upper!_API !PROJECT_NAME:upper!_EXPORT
#else
#define !PROJECT_NAME:upper!_API !PROJECT_NAME:upper!_IMPORT
#endif /* defined(!PROJECT_NAME:upper!_BUILD_SHARED) */

#if defined __cplusplus
#define !PROJECT_NAME:upper!_CPP_ENTER extern "C" {
#define !PROJECT_NAME:upper!_CPP_END }
#else
#define !PROJECT_NAME:upper!_CPP_ENTER
#define !PROJECT_NAME:upper!_CPP_END
#endif /* DEFINED __cplusplus */

#if !defined NULL
#define NULL (void*)0
#endif /* !defined NULL */

#if defined(!PROJECT_NAME:upper!_WIN)
#define !PROJECT_NAME:upper!_FUNCTION __FUNCTION__
#elif defined(!PROJECT_NAME:upper!_GCC) || defined(!PROJECT_NAME:upper!_CLANG)
#define !PROJECT_NAME:upper!_FUNCTION __PRETTY_FUNCTION__
#endif /* !PROJECT_NAME:upper!_WIN */

#define CONCAT_(prefix, suffix)     prefix##suffix
#define CONCAT(prefix, suffix)      CONCAT_(prefix, suffix)

#define STATIC_ASSERT(expr)                             \
    struct CONCAT(__outscope_assert_, __COUNTER__)      \
    {                                                   \
        char                                            \
        outscope_assert                                 \
        [2*(expr)-1];                                   \
                                                        \
    } CONCAT(__outscope_assert_, __COUNTER__)

#define !PROJECT_NAME:upper!_NOT_IMPLEMENTED std::fprintf(stderr, "Function " !PROJECT_NAME:upper!_FUNCTION " not implemented"); std::exit(1);

#define !PROJECT_NAME:upper!_NON_COPYABLE(__class__)                   \
    __class__(const __class__ &) = delete;                  \
    __class__(__class__ &&) = delete;                       \
    const __class__ &operator=(const __class__ &) = delete; \
    void operator=(__class__ &&) = delete;

#if defined(!PROJECT_NAME:upper!_MSVC)
#define !PROJECT_NAME:upper!_PACKED_STRUCT(__struct__) __pragma(pack(push, 1)) __struct__ __pragma(pack(pop))
#elif defined(!PROJECT_NAME:upper!_GCC) || defined(!PROJECT_NAME:upper!_CLANG)
#define !PROJECT_NAME:upper!_PACKED_STRUCT(__struct__) __struct__ __attribute__((__packed__))
#else
#define !PROJECT_NAME:upper!_PACKED_STRUCT(__struct__) __struct__
#endif /* defined(!PROJECT_NAME:upper!_MSVC) */

#if defined(!PROJECT_NAME:upper!_MSVC)
#define dump_struct(s) 
#elif defined(!PROJECT_NAME:upper!_CLANG)
#define dump_struct(s) __builtin_dump_struct(s, printf)
#elif defined(!PROJECT_NAME:upper!_GCC)
#define dump_struct(s) 
#endif /* defined(!PROJECT_NAME:upper!_MSVC) */

#if defined(DEBUG_BUILD)
#define !PROJECT_NAME:upper!_DEBUG 1
#else
#define !PROJECT_NAME:upper!_DEBUG 0
#endif /* defined(DEBUG_BUILD) */

#define !PROJECT_NAME:upper!_NAMESPACE_BEGIN namespace !PROJECT_NAME:lower! {
#define !PROJECT_NAME:upper!_NAMESPACE_END }

#define !PROJECT_NAME:upper!_ATEXIT_REGISTER(func, exit)                                       \
        int res_##func = std::atexit(func);                                         \
        if(res_##func != 0)                                                         \
        {                                                                           \
            std::fprintf(stderr, "Cannot register function \""#func"\" in atexit"); \
            if(exit) return 1;                                                      \
        }                                                                           \

#endif /* !defined(__!PROJECT_NAME:upper!) */
