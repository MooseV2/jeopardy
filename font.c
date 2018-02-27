#include <curses.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include "font_lookup.h"
int place_char(int x, int y, char c, bool draw) {
  int index = (int)(strchr(lookup_table, toupper(c)) - lookup_table);
  if (index < 0) index = 44;
  int offset = index * 12;
  if (draw) {
    mvaddwstr(y,x, &font_table[offset]);
    mvaddwstr(y+1,x, &font_table[offset+4]);
    mvaddwstr(y+2,x, &font_table[offset+8]);
  }
  return index;
}

int place_word(int x, int y, char *word) {
  for (int i=0; i<strlen(word); ++i) {
    x += font_lengths[place_char(x, y, word[i], true)];
  }
  return x;
}

int word_drawn_length(char *word) {
  int length = 0;
  while (*word++)
    length += font_lengths[place_char(0, 0, *word, false)];
  return length;
}

void draw_billboard(char *text, int vspacing) {
  // Max length
  const int max_line_length = 30;
  // Question text
  char question[300];
  char full_line[10][300] = { 0 };
  strcpy(question, text);
  // Bounds and borders
  int x, y, wx, wy;
  getmaxyx(stdscr, wy, wx);
  x = (wx-max_line_length*3)/2-1;
  int line = 0;
  clear();
  draw_rectangle(0, 0, wy-1, wx-1);
  draw_rectangle(3, 3, wy-4, wx-4);
  char *nextword = strtok(question, " ");
  while (nextword != NULL) {
    int current_len = strlen(full_line[line]);
    if (current_len + strlen(nextword) + 1 <= max_line_length) {
      if (current_len > 0) {
        full_line[line][current_len] = ' ';
        current_len++;
      }
      strcpy(full_line[line]+current_len, nextword);      
    } else {
      line++;
      current_len = strlen(nextword);
      strcpy(full_line[line], nextword);
    }
    nextword = strtok(NULL, " ");
  }

  y = (wy - ((3+vspacing)*line))/2 - 3;

  for (int i=0; i<=line; i++) {
    place_word((wx-word_drawn_length(&full_line[i]))/2, y+i*vspacing, full_line[i]);
  }
}