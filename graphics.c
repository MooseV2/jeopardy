#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include "graphics.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void draw_rectangle(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

void draw_init() {
  initscr();
  noecho();
  curs_set(0);
  start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
  keypad(stdscr, true);
  clear();
}

int string_offset(char *str) {
  return (int)(32-strlen(str))/2+1;
}

void mvprintc(char *text, int cx, int cy, int offx, int offy) {
  mvprintw(offy+cy*7+3, offx+cx*33+string_offset(text), text);
}

void draw_board() {
  draw_init();
  int cursor_x = 1, cursor_y = 1, sx=0, sy=6;
  const w = 33 * 6;
  const h = 7 * 7;
  while (true) {
    clear();
    // Main box
    for (int i=0; i<7; ++i) {
      mvhline(sy+i*7, sx, 0, w);
      mvvline(sy, sx+i*33, 0, h);
    }
    mvhline(sy+h, sx, 0, w);

    // Tee's
    for (int x=0; x<7; ++x) {
      for (int y=0; y<7; ++y) {
        mvaddch(sy+y*7, sx+x*33, ACS_PLUS);
        if (y == 0) mvaddch(sy, sx+x*33, ACS_TTEE);
        if (x == 0) mvaddch(sy+y*7, sx, ACS_LTEE);
        if (x == 6) mvaddch(sy+y*7, sx+w, ACS_RTEE);
        if (y == 6) mvaddch(sy+h, sx+x*33, ACS_BTEE);
      }
    }

    // Corners
    mvaddch(sy, sx, ACS_ULCORNER);
    mvaddch(sy, sx+w, ACS_URCORNER);
    mvaddch(sy+h, sx+w, ACS_LRCORNER);
    mvaddch(sy+h, sx, ACS_LLCORNER);

    // Cursor
    attron(COLOR_PAIR(1));
    mvaddch(sy+cursor_y*7+1, sx+cursor_x*33+1, ACS_ULCORNER);
    mvaddch(sy+cursor_y*7+1, sx+cursor_x*33+32, ACS_URCORNER);
    mvaddch(sy+cursor_y*7+6, sx+cursor_x*33+1, ACS_LLCORNER);
    mvaddch(sy+cursor_y*7+6, sx+cursor_x*33+32, ACS_LRCORNER);
    mvhline(sy+cursor_y*7+1, sx+cursor_x*33+2, 0, 30);
    mvhline(sy+cursor_y*7+6, sx+cursor_x*33+2, 0, 30);
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(1));
    mvprintw(0,0,"      _                                _       _ ");
    mvprintw(1,0,"     | | ___  ___  _ __   __ _ _ __ __| |_   _| |");
    mvprintw(2,0,"  _  | |/ _ \\/ _ \\| '_ \\ / _` | '__/ _` | | | | |");
    mvprintw(3,0," | |_| |  __/ (_) | |_) | (_| | | | (_| | |_| |_|");
    mvprintw(4,0,"  \\___/ \\___|\\___/| .__/ \\__,_|_|  \\__,_|\\__, (_)");
    mvprintw(5,0,"                  |_|                    |___/   ");
    attroff(COLOR_PAIR(1));

    int _x=0, _y=0;
    mvprintc("What", _x++, _y, sx, sy);
    mvprintc("the", _x++, _y, sx, sy);
    mvprintc("fuck", _x++, _y, sx, sy);
    mvprintc("did", _x++, _y, sx, sy);
    mvprintc("you", _x++, _y, sx, sy);
    mvprintc("just", _x++, _y, sx, sy);
    _y++; _x=0;
    mvprintc("fucking", _x++, _y, sx, sy);
    mvprintc("say", _x++, _y, sx, sy);
    mvprintc("about", _x++, _y, sx, sy);
    mvprintc("me,", _x++, _y, sx, sy);
    mvprintc("you", _x++, _y, sx, sy);
    mvprintc("little", _x++, _y, sx, sy);
    _y++; _x=0;
    mvprintc("bitch?", _x++, _y, sx, sy);
    mvprintc("I'll", _x++, _y, sx, sy);
    mvprintc("have", _x++, _y, sx, sy);
    mvprintc("you", _x++, _y, sx, sy);
    mvprintc("know", _x++, _y, sx, sy);
    mvprintc("I", _x++, _y, sx, sy);
    _y++; _x=0;
    mvprintc("graduated", _x++, _y, sx, sy);
    mvprintc("top", _x++, _y, sx, sy);
    mvprintc("of", _x++, _y, sx, sy);
    mvprintc("my", _x++, _y, sx, sy);
    mvprintc("class", _x++, _y, sx, sy);
    mvprintc("in", _x++, _y, sx, sy);
    _y++; _x=0;
    mvprintc("the", _x++, _y, sx, sy);
    mvprintc("Navy", _x++, _y, sx, sy);
    mvprintc("Seals,", _x++, _y, sx, sy);
    mvprintc("and", _x++, _y, sx, sy);
    mvprintc("I've", _x++, _y, sx, sy);
    mvprintc("been", _x++, _y, sx, sy);
    _y++; _x=0;
    mvprintc("involved", _x++, _y, sx, sy);
    mvprintc("in", _x++, _y, sx, sy);
    mvprintc("numerous", _x++, _y, sx, sy);
    mvprintc("secret", _x++, _y, sx, sy);
    mvprintc("raids", _x++, _y, sx, sy);
    mvprintc("on", _x++, _y, sx, sy);
    _y++; _x=0;
    mvprintc("Al-Quaeda,", _x++, _y, sx, sy);
    mvprintc("and", _x++, _y, sx, sy);
    mvprintc("I have over", _x++, _y, sx, sy);
    mvprintc("300", _x++, _y, sx, sy);
    mvprintc("confirmed", _x++, _y, sx, sy);
    mvprintc("kills", _x++, _y, sx, sy);

    int c = getch();
    switch (c) {
      case KEY_UP:
        cursor_y=MAX(1,cursor_y-1); break;
      case KEY_DOWN:
        cursor_y=MIN(6,cursor_y+1); break;
      case KEY_LEFT:
        cursor_x=MAX(0,cursor_x-1); break;
      case KEY_RIGHT:
        cursor_x=MIN(5,cursor_x+1); break;
      case KEY_ENTER:
      case 10: // Backup for enter
        goto END;
    }
    

    refresh();
  }
  END:
  clear();
  endwin();
}