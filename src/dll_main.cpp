#include "!PROJECT_NAME=lower!/!PROJECT_NAME=lower!.h"

#include <cstdio>

#if defined(!PROJECT_NAME=upper!_WIN)
#include <Windows.h>
#endif // defined(!PROJECT_NAME=upper!_WIN)

/* 
   In this source file we execute all functions that need to be executed at runtime to check and
   set some global variables (for simd vectorization, cpu frequency for profiling...) 

   lib_entry is executed on dlopen / LoadLibrary
   lib_exit is executed on dlclose / CloseLibrary
*/

void !PROJECT_NAME=upper!_LIB_ENTRY lib_entry(void)
{
#if !PROJECT_NAME=upper!_DEBUG
    std::printf("!PROJECT_NAME=lower! entry\n");
#endif // !PROJECT_NAME=upper!_DEBUG
}

void !PROJECT_NAME=upper!_LIB_EXIT lib_exit(void)
{
#if !PROJECT_NAME=upper!_DEBUG
    std::printf("!PROJECT_NAME=lower! exit\n");
#endif // !PROJECT_NAME=upper!_DEBUG
}

#if defined(!PROJECT_NAME=upper!_WIN)
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) 
{
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            /* Code to run when the DLL is loaded */
            lib_entry();
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            /* Code to run when the DLL is unloaded */
            lib_exit();
            break;
    }

    return TRUE;
}
#endif // defined(!PROJECT_NAME=upper!_WIN)