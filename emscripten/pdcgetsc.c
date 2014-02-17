/* Public Domain Curses */

#include "pdcemscripten.h"

RCSID("$Id: pdcgetsc.c,v 1.8 2008/07/14 04:24:52 wmcbrine Exp $")

/* get the cursor size/shape */

int PDC_get_cursor_mode(void)
{
    PDC_LOG(("PDC_get_cursor_mode() - called\n"));

    return EM_ASM_INT_V({
        return term.crsrBlinkMode ? 0 : term.crsrBlockMode ? 1 : 2;
    });
}

/* return number of screen rows */

int PDC_get_rows(void)
{
    PDC_LOG(("PDC_get_rows() - called\n"));

    /* FIXME: should return the rows that fit into termDiv */
    return EM_ASM_INT_V({
        return term.conf.rows;
    });
}

/* return width of screen/viewport */

int PDC_get_columns(void)
{
    PDC_LOG(("PDC_get_columns() - called\n"));

    /* FIXME: should return the cols that fit into termDiv */
    return EM_ASM_INT_V({
        return term.conf.cols;
    });
}
