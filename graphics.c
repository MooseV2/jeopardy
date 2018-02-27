#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <unistd.h>
#include "utilities.h"
#include "graphics.h"
#include "players.h"
#include "questions.h"
#include "font.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int cursor_x = 1, cursor_y = 1;

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
    if (players[i].turn == true) {
      attron(COLOR_PAIR(5));
      char controlText[100];
      sprintf(controlText, "%s has control of the board.", players[i].name);
      mvprintw(sy+7*6+6, 1, controlText);
    }

    mvprintw(sy+i, sx, players[i].name);
    char dollars[10];
    sprintf(dollars, "$%d", players[i].score);
    mvprintw(sy+i, sx+27, dollars);
    attroff(COLOR_PAIR(5));
    
  }
}

void print_categories(struct Category *categories, int sx, int sy, bool double_jeopardy) {
  for (int i=0; i<6; ++i) {
    mvprintc(categories[i].name, i, 0, sx, sy);
    for (int j=0; j<5; ++j) {
      if (!categories[i].questions[j].answered) {
        char priceValue[10];
        sprintf(priceValue, "$%d", categories[i].questions[j].value);
        mvprintc(priceValue, i, j+1, sx, sy);
      }
    }
  }
}

void draw_init() {
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  curs_set(0);
  start_color();
  // init_color(COLOR_BLUE, 24, 48, 913);
  init_color(COLOR_BLUE, 400, 600, 900);
  init_color(COLOR_GREEN, 600, 900, 600);
  init_color(COLOR_MAGENTA, 200, 200, 200);
  init_color(COLOR_RED, 900, 200, 200);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_BLUE);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_BLACK, COLOR_RED);
  init_pair(7, COLOR_BLACK, COLOR_GREEN);
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

void draw_board(struct Player *players, struct Category *categories, bool double_jeopardy, struct Question **chosenQuestion) {
  draw_init();
  int sx=0, sy=7;
  const int w = 33 * 6;
  const int h = 6 * 7;
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
    
    print_categories(categories, sx, sy, double_jeopardy);
    refresh();
    int c = getch();
    switch (c) {
      case KEY_UP:
        cursor_y=MAX(1,cursor_y-1); break;
      case KEY_DOWN:
        cursor_y=MIN(5,cursor_y+1); break;
      case KEY_LEFT:
        cursor_x=MAX(0,cursor_x-1); break;
      case KEY_RIGHT:
        cursor_x=MIN(5,cursor_x+1); break;
      case KEY_ENTER:
      case 10: // Backup for enter
        if (!categories[cursor_x].questions[cursor_y-1].answered) {
          *chosenQuestion = &categories[cursor_x].questions[cursor_y-1];
          goto END;
        }
          
    }
    
    refresh();
  }
  END:
  clear();
  endwin();
}


void flash_correct(bool correct) {
  wbkgd(stdscr, COLOR_PAIR(correct ? 7 : 6));
  refresh();
  usleep(600000);
  wbkgd(stdscr, use_default_colors());
  refresh();
}
bool request_answer(struct Player player, struct Question *question) {
  char *answer = (char*)calloc(200, sizeof(char));
  int wx, wy;
  getmaxyx(stdscr, wy, wx);
  attron(COLOR_PAIR(5));
  mvprintw(wy-3, 4, "%s is answering:", player.name);
  echo();
  curs_set(true);
  refresh();
  keypad(stdscr, false);
  flushinp();
  move(wy-2, 4);
  getnstr(answer, 200);
  curs_set(false);
  noecho();
  bool correct = verify_answer(question->answer, answer);
  attroff(COLOR_PAIR(5));
  flash_correct(correct);
  mvhline(wy-3, 4, ' ', 100);
  mvhline(wy-2, 4, ' ', 100);
  return correct;
}

int draw_question_board(struct Question *question, struct Player *player_list, int n_players, int *already_buzzed) {
  draw_init();
  if (*already_buzzed == (int)pow(2,n_players)-1) return -1; // Break if needed
  clear();
  draw_billboard(question->question, 5);
  keypad(stdscr, false);
  refresh();
  
  while (true) {
    timeout(20000);
    int c = getch();
    if (c == ERR) {
      flash_correct(false);
      return -1;
    }
    char buzzedin = 0;
    for (int element=0; element<n_players; element++) {
      if (c == player_list[element].buzzer) {
        buzzedin = 1<<element;
        if (!(buzzedin & *already_buzzed)) { // Valid press
          *already_buzzed = *already_buzzed | buzzedin;
          return element;
        }
      }
    }
  }
  clear();
  endwin();
}