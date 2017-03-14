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

# testcurs.html fails to build and tuidemo.html fails to run
DEMOS		= firework.html newdemo.html ptest.html rain.html \
			  worm.html xmas.html
DEMOFLAGS	= $(CFLAGS) --shell-file template.html \
			  -s EMTERPRETIFY=1 -s EMTERPRETIFY_ASYNC=1

.PHONY: all libs clean demos

all:	libs demos

libs:	$(LIBCURSES)

clean:
	-rm -rf *.o trace $(LIBCURSES) $(DEMOS) $(DEMOS:.html=.js) \
	        $(DEMOS:.html=.html.mem)

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

firework.html: firework.c
	$(CC) -I.. $(DEMOFLAGS) \
	      -o $@ $< $(LDFLAGS)

newdemo.html: $(demodir)/newdemo.c
	$(BUILD) $(DEMOFLAGS) -o $@ $< $(LDFLAGS)

ptest.html: $(demodir)/ptest.c
	$(BUILD) $(DEMOFLAGS) -o $@ $< $(LDFLAGS)

rain.html: rain.c
	$(CC) -I.. $(CFLAGS) --shell-file template.html -o $@ $< $(LDFLAGS)

testcurs.html: $(demodir)/testcurs.c
	$(BUILD) $(DEMOFLAGS) -o $@ $< $(LDFLAGS)

tuidemo.html: tuidemo.o tui.o
	$(LINK) tui.o tuidemo.o -o $@ $(LDFLAGS)

worm.html: $(demodir)/worm.c
	$(BUILD) $(DEMOFLAGS) -o $@ $< $(LDFLAGS)

xmas.html: $(demodir)/xmas.c
	$(BUILD) $(DEMOFLAGS) -o $@ $< $(LDFLAGS)

tui.o: $(demodir)/tui.c $(demodir)/tui.h
	$(BUILD) -c $(DEMOFLAGS) $(demodir)/tui.c

tuidemo.o: $(demodir)/tuidemo.c
	$(BUILD) -c $(DEMOFLAGS) $(demodir)/tuidemo.c
