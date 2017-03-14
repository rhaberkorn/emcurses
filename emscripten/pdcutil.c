/* Public Domain Curses */

#include <emscripten.h>

#include "pdcemscripten.h"

RCSID("$Id: pdcutil.c,v 1.6 2008/07/14 04:24:52 wmcbrine Exp $")

void PDC_beep(void)
{
    PDC_LOG(("PDC_beep() - called\n"));
    /* FIXME */
}

void PDC_napms(int ms)
{
    /* This is a synchronous sleep, which isn't normally possible with
     * Emscripten. Code using it must be compiled with -s EMTERPRETIFY=1
     * -s EMTERPRETIFY_ASYNC=1, and all functions in the call graph leading
     * to this sleep must use the Emterpreter. For more information, see:
     * https://github.com/kripken/emscripten/wiki/Emterpreter
     */
    emscripten_sleep(ms);
    PDC_LOG(("PDC_napms() - called: ms=%d\n", ms));
}

const char *PDC_sysname(void)
{
    return "emscripten";
}
