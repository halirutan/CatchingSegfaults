#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include "WolframLibrary.h"


DLLEXPORT mint WolframLibrary_getVersion() {
    return WolframLibraryVersion;
}


DLLEXPORT int WolframLibrary_initialize(WolframLibraryData libData) {
    return 0;
}

DLLEXPORT void WolframLibrary_uninitialize(WolframLibraryData libData) {

    return;
}

sigjmp_buf point;

static void handler(int sig, siginfo_t *dont_care, void *dont_care_either) {
    longjmp(point, 1);
}

static void do_segv() {
    int *segv;
    segv = 0;
    *segv = 1;
}


DLLEXPORT int catchSegfault(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
    mint i = MArgument_getInteger(Args[0]);
    if (i == 0) {
        do_segv();
        return LIBRARY_NO_ERROR;
    } else {
        struct sigaction sa;

        memset(&sa, 0, sizeof(sigaction));
        sigemptyset(&sa.sa_mask);

        sa.sa_flags = SA_NODEFER;
        sa.sa_sigaction = handler;

        sigaction(SIGSEGV, &sa, NULL); /* ignore whether it works or not */

        if (setjmp(point) == 0) {
            do_segv();
            return LIBRARY_NO_ERROR;
        } else {
            return LIBRARY_MEMORY_ERROR;
        }
    }
}
