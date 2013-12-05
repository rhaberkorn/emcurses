/* Public Domain Curses */

#include "pdcemscripten.h"

RCSID("$Id: pdcgetsc.c,v 1.8 2008/07/14 04:24:52 wmcbrine Exp $")

/* get the cursor size/shape */

int PDC_get_cursor_mode(void)
{
    int ret;
    PDC_LOG(("PDC_get_cursor_mode() - called\n"));

    asm("term.crsrBlinkMode ? 0 : term.crsrBlockMode ? 1 : 2;"
       :"=r"(ret));
    return ret;
}

/* return number of screen rows */

int PDC_get_rows(void)
{
    int rows;
    PDC_LOG(("PDC_get_rows() - called\n"));

    /* FIXME: should return the rows that fit into termDiv */
    asm("term.conf.rows;" :"=r"(rows));
    return rows;
}

/* return width of screen/viewport */

int PDC_get_columns(void)
{
    int cols;
    PDC_LOG(("PDC_get_columns() - called\n"));

    /* FIXME: should return the cols that fit into termDiv */
    asm("term.conf.cols;" :"=r"(cols));
    return cols;
}
