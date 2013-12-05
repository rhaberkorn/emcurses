/* Public Domain Curses */

#include "pdcemscripten.h"

RCSID("$Id: pdcutil.c,v 1.6 2008/07/14 04:24:52 wmcbrine Exp $")

void PDC_beep(void)
{
    PDC_LOG(("PDC_beep() - called\n"));
    /* FIXME */
}

void PDC_napms(int ms)
{
    PDC_LOG(("PDC_napms() - called: ms=%d\n", ms));
}

const char *PDC_sysname(void)
{
    return "emscripten";
}
