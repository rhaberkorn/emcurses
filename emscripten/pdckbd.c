/* Public Domain Curses */

#include "pdcemscripten.h"

RCSID("$Id: pdckbd.c,v 1.20 2008/07/14 04:24:52 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         pdckbd

  Synopsis:
        unsigned long PDC_get_input_fd(void);

  Description:
        PDC_get_input_fd() returns the file descriptor that PDCurses 
        reads its input from. It can be used for select().

  Portability                                X/Open    BSD    SYS V
        PDC_get_input_fd                        -       -       -

**man-end****************************************************************/

#include <string.h>

unsigned long PDC_get_input_fd(void)
{
    PDC_LOG(("PDC_get_input_fd() - called\n"));

    return 0L;  /* test this */
}

void PDC_set_keyboard_binary(bool on)
{
    PDC_LOG(("PDC_set_keyboard_binary() - called\n"));
}

/* check if a key or mouse event is waiting */

bool PDC_check_key(void)
{
    if ((PDC_get_columns() != SP->cols ||
         PDC_get_rows() != SP->lines) && !SP->resized)
	return TRUE;

    return EM_ASM_INT_V({
        return term.inputChar;
    }) ? TRUE : FALSE;
}

/* return the next available key or mouse event */

int PDC_get_key(void)
{
    int c = EM_ASM_INT_V({
        var c = term.inputChar;
        term.inputChar = 0;
        return c;
    });
    int key = 0;

    switch (c) {
    case 0x7F: /* DEL */
        key = KEY_DC;
        break;
    case 0x1C: /* LEFT */
        key = KEY_LEFT;
        break;
    case 0x1D: /* RIGHT */
        key = KEY_RIGHT;
        break;
    case 0x1E: /* UP */
        key = KEY_UP;
        break;
    case 0x1F: /* DOWN */
        key = KEY_DOWN;
        break;
    default:
        key = c;
        break;
    }
    SP->key_code = (key > 0x100);

    if (!key) {
        if ((PDC_get_columns() != SP->cols ||
             PDC_get_rows() != SP->lines) && !SP->resized) {
            SP->resized = TRUE;
            key = KEY_RESIZE;
        }
    }

    return key ? key : -1;
}

/* discard any pending keyboard or mouse input -- this is the core
   routine for flushinp() */

void PDC_flushinp(void)
{
    PDC_LOG(("PDC_flushinp() - called\n"));

    EM_ASM(term.inputChar = 0);
}

int PDC_mouse_set(void)
{
    return ERR;
}

int PDC_modifiers_set(void)
{
    return OK;
}
