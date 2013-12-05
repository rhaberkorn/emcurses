/* Public Domain Curses */

#include "pdcemscripten.h"

#include <stdlib.h>
#include <stdio.h>

/* COLOR_PAIR to attribute encoding table. */

static struct {short f, b;} atrtab[PDC_COLOR_PAIRS];

void PDC_scr_close(void)
{
    PDC_LOG(("PDC_scr_close() - called\n"));
    asm("term.close();");
}

void PDC_scr_free(void)
{
    if (SP)
        free(SP);
}

/* open the physical screen -- allocate SP, miscellaneous intialization */

int PDC_scr_open(int argc, char **argv)
{
    PDC_LOG(("PDC_scr_open() - called\n"));

    SP = calloc(1, sizeof(SCREEN));

    if (!SP)
        return ERR;

    /* FIXME: allow registering a C callback that gets called asynchronously
       from the handler.
       Also for screen resize events, etc.
     */
    EM_ASM(
        term = new Terminal({
            termDiv: 'termDiv',
            handler: function() {},
            x: 0, y: 0,
            initHandler: function() {
                term.charMode = true;
                term.lock = false;
                term.cursorOn();
            }
        });
        term.open();
    );

    SP->mono = 0;
    SP->orig_attr = FALSE;

    const char *PDC_LINES = getenv("PDC_LINES"),
	       *PDC_COLS = getenv("PDC_COLS");
    if (PDC_COLS && PDC_LINES) {
        asm("term.resizeTo(%0, %1);"
           ::"r"(atoi(PDC_COLS)), "r"(atoi(PDC_LINES)));
    }

    SP->lines = PDC_get_rows();
    SP->cols = PDC_get_columns();

    /* FIXME: we could actually beep */
    SP->audible = FALSE;

    PDC_reset_prog_mode();

    return OK;
}

/* the core of resize_term() */

int PDC_resize_screen(int nlines, int ncols)
{
    asm("term.resizeTo(%0, %1);"
       ::"r"(ncols), "r"(nlines));

    SP->resized = FALSE;
    SP->cursrow = SP->curscol = 0;

    return OK;
}

void PDC_reset_prog_mode(void)
{
    PDC_LOG(("PDC_reset_prog_mode() - called.\n"));

//    PDC_flushinp();
//    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}

void PDC_reset_shell_mode(void)
{
    PDC_LOG(("PDC_reset_shell_mode() - called.\n"));

//    SDL_EnableKeyRepeat(0, 0);
//    PDC_flushinp();
}

void PDC_restore_screen_mode(int i)
{
//    asm("term.restoreScreen();"); /* FIXME */
}

void PDC_save_screen_mode(int i)
{
//    asm("term.backupScreen();"); /* FIXME */
}

void PDC_init_pair(short pair, short fg, short bg)
{
    atrtab[pair].f = fg;
    atrtab[pair].b = bg;
}

int PDC_pair_content(short pair, short *fg, short *bg)
{
    *fg = atrtab[pair].f;
    *bg = atrtab[pair].b;

    return OK;
}

bool PDC_can_change_color(void)
{
    return TRUE;
}

int PDC_color_content(short color, short *red, short *green, short *blue)
{
    char str[8];
    int r, g, b;

    asm("TermGlobals.getColorString(%0);"
       :"=r"(str) :"r"(color));
    sscanf(str, "#%02x%02x%02x", &r, &g, &b);

    *red = DIVROUND(r * 1000, 255);
    *green = DIVROUND(g * 1000, 255);
    *blue = DIVROUND(b * 1000, 255);

    return OK;
}

int PDC_init_color(short color, short red, short green, short blue)
{
    char str[8];

    int r = DIVROUND(red * 255, 1000);
    int g = DIVROUND(green * 255, 1000);
    int b = DIVROUND(blue * 255, 1000);

    sprintf(str, "#%02x%02x%02x", r, g, b);
    asm("TermGlobals.setColor(%0, %1);"
       ::"r"(color), "r"(str));

    wrefresh(curscr);

    return OK;
}
