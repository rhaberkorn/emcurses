# Makefile for PDCurses library for SDL

O = o

ifndef PDCURSES_SRCDIR
	PDCURSES_SRCDIR	= ..
endif

include $(PDCURSES_SRCDIR)/libobjs.mif

osdir		= $(PDCURSES_SRCDIR)/emscripten

PDCURSES_EMSCRIPTEN_H	= $(osdir)/pdcemscripten.h

# If your system doesn't have these, remove the defines here
SFLAGS		+= -DHAVE_VSNPRINTF -DHAVE_VSSCANF

ifeq ($(DEBUG),Y)
	CFLAGS  = -g -Wall -DPDCDEBUG
else
	CFLAGS  = -O2 -Wall
endif

BUILD		= $(CC) $(CFLAGS) -I$(PDCURSES_SRCDIR)

LINK		= $(CC)
LDFLAGS	= --pre-js termlib.js $(LIBCURSES)
LIBCURSES	= libpdcurses.so

DEMOS		= firework.js rain.js
DEMOFLAGS	= -O2

.PHONY: all libs clean demos

all:	libs demos

libs:	$(LIBCURSES)

clean:
	-rm -rf *.o trace $(LIBCURSES) $(DEMOS)

demos:	$(DEMOS)

$(LIBCURSES) : $(LIBOBJS) $(PDCOBJS)
	$(CC) $(CFLAGS) -shared $^ -o $@

$(LIBOBJS) $(PDCOBJS) : $(PDCURSES_HEADERS)
$(PDCOBJS) : $(PDCURSES_SDL_H)
$(DEMOS) : $(PDCURSES_CURSES_H) $(LIBCURSES)
tui.o tuidemo.o : $(PDCURSES_CURSES_H)
terminfo.o: $(TERM_HEADER)
panel.o ptest: $(PANEL_HEADER)

$(LIBOBJS) : %.o: $(srcdir)/%.c
	$(BUILD) $(SFLAGS) -c $<

$(PDCOBJS) : %.o: $(osdir)/%.c
	$(BUILD) $(SFLAGS) -c $<

firework.js: firework.c
	$(CC) -I.. $(DEMOFLAGS) -o $@ $< $(LDFLAGS)

rain.js: rain.c
	$(CC) -I.. $(DEMOFLAGS) -o $@ $< $(LDFLAGS)
