#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include "graphics.h"
#include "players.h"
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

void print_player_scores(int sx, int sy, struct Player *players) {
  for (int i=0; i<4; ++i) {
    mvprintw(sy+i, sx, players[i].name);
    char dollars[10];
    sprintf(dollars, "$%d", players[i].score);
    mvprintw(sy+i, sx+28, dollars);
  }
}

void draw_init() {
  initscr();
  noecho();
  curs_set(0);
  start_color();
  // init_color(COLOR_BLUE, 24, 48, 913);

	init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_BLUE);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
  init_color(COLOR_GREEN, 200, 200, 200);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  keypad(stdscr, true);
  clear();
}

int string_offset_x(char *str, int offset) {
  return (int)(offset-strlen(str))/2+1;
}
int string_offset(char *str) {
  return string_offset_x(str, 32);
}

void mvprintc(char *text, int cx, int cy, int offx, int offy) {
  mvprintw(offy+cy*7+3, offx+cx*33+string_offset(text), text);
}

void draw_board(struct Player *players) {
  draw_init();
  int cursor_x = 1, cursor_y = 1, sx=0, sy=7;
  const w = 33 * 6;
  const h = 6 * 7;
  while (true) {
    clear();
    // Main box
    for (int i=0; i<7; ++i) {
      mvhline(sy+i*7, sx, 0, w);
      mvvline(sy, sx+i*33, 0, h);
    }
    mvhline(sy+h, sx, 0, w);

    // Tee's
    for (int x=0; x<6; ++x) {
      for (int y=0; y<6; ++y) {
        mvaddch(sy+y*7, sx+x*33, ACS_PLUS);
        if (y == 0) mvaddch(sy, sx+x*33, ACS_TTEE);
        if (x == 0) mvaddch(sy+y*7, sx, ACS_LTEE);
        if (x == 5) mvaddch(sy+y*7, sx+w, ACS_RTEE);
        if (y == 5) mvaddch(sy+h, sx+x*33, ACS_BTEE);
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
    attron(A_BOLD);
    mvprintw(0,w-52,"      _                                _       _ ");
    mvprintw(1,w-52,"     | | ___  ___  _ __   __ _ _ __ __| |_   _| |");
    mvprintw(2,w-52,"  _  | |/ _ \\/ _ \\| '_ \\ / _` | '__/ _` | | | | |");
    mvprintw(3,w-52," | |_| |  __/ (_) | |_) | (_| | | | (_| | |_| |_|");
    mvprintw(4,w-52,"  \\___/ \\___|\\___/| .__/ \\__,_|_|  \\__,_|\\__, (_)");
    mvprintw(5,w-52,"                  |_|                    |___/   ");
    attroff(COLOR_PAIR(1));
    attroff(A_BOLD);
    attron(A_UNDERLINE);
    attron(COLOR_PAIR(4));
    for (int i=1;i<6;++i)
      mvhline(i,16, i == 1 ? ' ' : '.', 34);
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(1));
    attron(A_BOLD);
    char *scoreboard_text = "~~~* S C O R E B O A R D *~~~";
    attroff(A_BOLD);
    mvprintw(1,16+string_offset_x(scoreboard_text, 34), scoreboard_text);
    attroff(COLOR_PAIR(1));
    // attroff(COLOR_PAIR(3));
    
    draw_rectangle(sy-7, sx+16, sy-1, sx+50);

    print_player_scores(17, 2, players);
    attroff(A_UNDERLINE);
    

    refresh();
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