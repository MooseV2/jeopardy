#include <ncurses.h>
#include <stdbool.h>
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

void draw_board() {
  int cx = 1, cy = 1;
  initscr();
  // noecho();
  curs_set(0);
  start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
  const w = 33 * 6;
  const h = 7 * 7;
  while (true) {
    clear();
    keypad(stdscr, true);
    
    // Main box
    for (int i=0; i<7; ++i) {
      mvhline(i*7, 0, 0, w);
      mvvline(0, i*33, 0, h);
    }
    mvhline(h, 0, 0, w);

    for (int x=0; x<7; ++x) {
      for (int y=0; y<7; ++y) {
        mvaddch(y*7, x*33, ACS_PLUS);
        if (y == 0) mvaddch(0, x*33, ACS_TTEE);
        if (x == 0) mvaddch(y*7, 0, ACS_LTEE);
        if (x == 6) mvaddch(y*7, w, ACS_RTEE);
        if (y == 6) mvaddch(h, x*33, ACS_BTEE);
      }
    }
    mvaddch(0, 0, ACS_ULCORNER);
    mvaddch(0, w, ACS_URCORNER);
    mvaddch(h, w, ACS_LRCORNER);
    mvaddch(h, 0, ACS_LLCORNER);

    attron(COLOR_PAIR(1));
    mvaddch(cy*7+1, cx*33+1, ACS_ULCORNER);
    mvaddch(cy*7+1, cx*33+32, ACS_URCORNER);
    mvaddch(cy*7+6, cx*33+1, ACS_LLCORNER);
    mvaddch(cy*7+6, cx*33+32, ACS_LRCORNER);
    mvhline(cy*7+1, cx*33+2, 0, 30);
    mvhline(cy*7+6, cx*33+2, 0, 30);
    attroff(COLOR_PAIR(1));
    int c = getch();
    switch (c) {
      case KEY_UP:
        cy=MAX(1,cy-1); break;
      case KEY_DOWN:
        cy=MIN(6,cy+1); break;
      case KEY_LEFT:
        cx=MAX(0,cx-1); break;
      case KEY_RIGHT:
        cx=MIN(6,cx+1); break;
      default:
        mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
        refresh();
    }
    
    refresh();
  }
  endwin();
}