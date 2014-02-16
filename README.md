# EMCurses: Terminate your Browser!

EMCurses is a port of [PDCurses](http://pdcurses.sourceforge.net/) to HTML/Javascript.
It requires [Emscripten](https://github.com/kripken/emscripten) and can be linked to
other applications compiled with Emscripten.
It is not merely PDCurses/SDL compiled with Emscripten - which cannot be done easily
anyway - but a distinct port that uses the [termlib](http://www.masswerk.at/termlib/)
Javascript library for output.

In essence, EMCurses helps you in porting your favourite terminal-based applications to
the Web platform; or in designing Web pages in the environment you are accustomed to:
the terminal and C programming language.

EMCurses is a work in progress and only a quick hack so far.
It's already functional, though.

## Installation

    cd emscripten/
    emmake make

This will produce a `libpdcurses.so`. When linking it with
a Curses application, you should preload `termlib.js`.
For example, the PDCurses `rain.c` example is compiled/linked
as follows:

    emcc -I.. -o rain.js rain.c --pre-js termlib.js libpdcurses.so

See e.g. `rain.html` for an example of embedding an EMCurses
application into a Webpage.
