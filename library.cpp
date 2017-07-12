#include <iostream>
#include <stdexcept>
#include <string>
#include "segvcatch.h"
#include "WolframLibrary.h"

using namespace std;

void handle_segv()
{
    throw std::runtime_error("My SEGV");
}

void handle_fpe()
{
    throw std::runtime_error("My FPE");
}

DLLEXPORT mint WolframLibrary_getVersion( ) {
    return WolframLibraryVersion;
}


DLLEXPORT int WolframLibrary_initialize( WolframLibraryData libData) {
    return 0;
}

DLLEXPORT void WolframLibrary_uninitialize(WolframLibraryData libData ) {

    return;
}


EXTERN_C DLLEXPORT int procudeSegfault(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
    try
    {
        *(int*) 0 = 0;
        MArgument_setInteger(Res, 1);
        return LIBRARY_NO_ERROR;
    }
    catch (std::exception& e)
    {
        MArgument_setInteger(Res, -1);
        return LIBRARY_MEMORY_ERROR;
    }
}
