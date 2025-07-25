# SPDX-License-Identifier: BSD-3-Clause 
# Copyright (c) !YEAR! - Present !AUTHOR!
# All rights reserved. 

function(set_target_options target_name)
    if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
        set(!PROJECT_NAME=upper!_CLANG 1)
        set(CMAKE_C_FLAGS "-Wall -pedantic-errors")

        set(COMPILE_OPTIONS -Wall $<$<CONFIG:Debug,RelWithDebInfo>:-fsanitize=leak -fsanitize=address> $<$<CONFIG:Release,RelWithDebInfo>:-O3> -mavx2 -mfma)

        target_compile_options(${target_name} PRIVATE $<$<COMPILE_LANGUAGE:C>:${COMPILE_OPTIONS}>)
        target_compile_options(${target_name} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${COMPILE_OPTIONS}>)

        target_link_options(${target_name} PRIVATE $<$<CONFIG:Debug,RelWithDebInfo>:-fsanitize=address>)
    elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set(!PROJECT_NAME=upper!_GCC 1)

        set(COMPILE_OPTIONS -D_FORTIFY_SOURCES=2 -pipe -Wall -pedantic-errors $<$<CONFIG:Debug,RelWithDebInfo>:-fsanitize=leak -fsanitize=address> $<$<CONFIG:Release,RelWithDebInfo>:-O3 -ftree-vectorizer-verbose=2> -mveclibabi=svml -mavx2 -mfma)

        target_compile_options(${target_name} PRIVATE $<$<COMPILE_LANGUAGE:C>:${COMPILE_OPTIONS}>)
        target_compile_options(${target_name} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${COMPILE_OPTIONS}>)
        
        target_link_options(${target_name} PRIVATE $<$<CONFIG:Debug,RelWithDebInfo>:-fsanitize=address>)
    elseif (CMAKE_C_COMPILER_ID STREQUAL "Intel")
        set(!PROJECT_NAME=upper!_INTEL 1)
    elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        set(!PROJECT_NAME=upper!_MSVC 1)
        include(find_avx)

        # 4710 is "Function not inlined", we don't care it pollutes more than tells useful information about the code
        # 5045 is "Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified", again we don't care
        set(COMPILE_OPTIONS /W1 /wd4710 /wd5045 ${AVX_FLAGS} $<$<CONFIG:Debug,RelWithDebInfo>:/fsanitize=address> $<$<CONFIG:Release,RelWithDebInfo>:/O2 /GF /Ot /Oy /GT /GL /Oi /Zi /Gm- /Zc:inline /Qpar>)

        target_compile_options(${target_name} PRIVATE $<$<COMPILE_LANGUAGE:C>:${COMPILE_OPTIONS}>)
        target_compile_options(${target_name} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${COMPILE_OPTIONS}>)

        # 4300 is "ignoring '/INCREMENTAL' because input module contains ASAN metadata", and we do not care
        set_target_properties(${target_name} PROPERTIES LINK_FLAGS "/ignore:4300")
        set_target_properties(${target_name} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:library")
    endif()

    # Provides the macro definition DEBUG_BUILD
    target_compile_definitions(${target_name} PRIVATE $<$<CONFIG:Debug>:DEBUG_BUILD>)
endfunction()
