#include <curses.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>

#define cz L"\0"
#define c0 L"╸"
#define c1 L"┻"
#define c2 L"╹"
#define c3 L"┫"
#define c4 L"╻"
#define c5 L"┣"
#define c6 L"━"
#define c7 L"╋"
#define c8 L"┓"
#define c9 L"┏"
#define ca L"╺"
#define cb L"┛"
#define cc L"┃"
#define cd L" "
#define ce L"┳"
#define cf L"┗"

const char *lookup_table = "0123456789:;=?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]_' .";

const wchar_t *font_table = 
   /* 0 1 2  */ c9 c6 c8 cz cc cc cc cz cf c6 cb cz   ca c8 cd cz cd cc cd cz ca c1 c0 cz   c9 c6 c8 cz c9 c6 cb cz cf c6 c0 cz
   /* 3 4 5  */ c9 c6 c8 cz ca c6 c3 cz cf c6 cb cz   c4 cd c4 cz cf c6 c3 cz cd cd c2 cz   c9 c6 c0 cz cf c6 c8 cz cf c6 cb cz
   /* 6 7 8  */ c9 c6 c8 cz c5 c6 c8 cz cf c6 cb cz   c9 c6 c8 cz cd cd cc cz cd cd c2 cz   c9 c6 c8 cz c5 c6 c3 cz cf c6 cb cz
   /* 9 : ;  */ c9 c6 c8 cz cf c6 c3 cz cf c6 cb cz   cd cb cb cz c2 cb cb cz c2 cb cb cz   cd cd cb cz cd c2 cb cz cd cb cb cz
   /* = ? @  */ cd cd cd cz ca c6 c0 cz ca c6 c0 cz   c9 c6 c8 cz cd ca cb cz cd c2 cd cz   c9 c6 c8 cz cc c5 cb cz cf c6 c0 cz
   /* A B C  */ c9 c6 c8 cz c5 c6 c3 cz c2 cd c2 cz   c9 c8 cd cz c5 c1 c8 cz cf c6 cb cz   c9 c6 c0 cz cc cd cd cz cf c6 c0 cz
   /* D E F  */ ca ce c8 cz cd cc cc cz ca c1 cb cz   c9 c6 c0 cz c5 c0 cd cz cf c6 c0 cz   c9 c6 c0 cz c5 c0 cd cz c2 cd cd cz
   /* G H I  */ c9 c6 c0 cz cc ca c8 cz cf c6 cb cz   c4 cd c4 cz c5 c6 c3 cz c2 cd c2 cz   c4 cb cb cz cc cb cb cz c2 cb cb cz
   /* J K L  */ cd c9 c8 cz cd cd cc cz cf c6 cb cz   c4 c9 cd cz c5 c1 c8 cz c2 cd c2 cz   c4 cd cd cz cc cd cd cz cf c6 c0 cz
   /* M N O  */ c9 ce c8 cz cc cc cc cz c2 cd c2 cz   c9 c8 c4 cz cc cf c3 cz c2 cd c2 cz   c9 c6 c8 cz cc cd cc cz cf c6 cb cz
   /* P Q R  */ c9 c6 c8 cz c5 c6 cb cz c2 cd cd cz   c9 c6 c8 cz cc c8 cc cz cf c1 cb cz   c9 c6 c8 cz c5 ce cb cz c2 cf c0 cz
   /* S T U  */ c9 c6 c8 cz cf c6 c8 cz cf c6 cb cz   ca ce c0 cz cd cc cd cz cd c2 cd cz   c4 cd c4 cz cc cd cc cz cf c6 cb cz
   /* V W X  */ c4 cd c4 cz cc c9 cb cz cf cb cd cz   c4 cd c4 cz cc c4 cc cz cf c1 cb cz   c4 cd c4 cz c9 c7 cb cz c2 cd c2 cz
   /* Y Z [  */ c4 cd c4 cz cf ce cb cz cd c2 cd cz   ca c6 c8 cz c9 c6 cb cz cf c6 c0 cz   c9 c6 cd cz cc cd cd cz cf c6 cd cz
   /* \ ] _  */ c4 cd cb cz cf c8 cb cz cd c2 cb cz   cd c6 c8 cz cd cd cc cz cd c6 cb cz   cd cd cd cz cd cd cd cz ca c6 c0 cz
   /* '   .  */ cd c8 cb cz cd cd cb cz cd cd cd cz   cd cd cd cz cd cd cd cz cd cd cd cz   cd cd cd cz cd cd cd cz c0 cd cd cz;

const int font_lengths[] = {3,3,3,3,3,3,3,3,3,3,1,2,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,2,3,1};

int draw_char(int x, int y, char c) {
  int index = (int)(strchr(lookup_table, toupper(c)) - lookup_table);
  if (index < 0) index = 44;
  int offset = index * 12;
  mvaddwstr(y,x, &font_table[offset]);
  mvaddwstr(y+1,x, &font_table[offset+4]);
  mvaddwstr(y+2,x, &font_table[offset+8]);
  return index;
}

int draw_word(int x, int y, char *word) {
  for (int i=0; i<strlen(word); ++i) {
    x += font_lengths[draw_char(x, y, word[i])];
  }
  return x;
}

void draw_question(int x, int y, int line_len, char *text, int vspacing) {
  char question[300];
  strcpy(question, text);
  int line = 0;
  char *nextword;
  nextword = strtok(question, " ");
  int current_len = 0;
  int cursor = x;

  while (nextword != NULL)
  {
    
    current_len += strlen(&nextword);
    cursor = draw_word(cursor, y+line*vspacing, nextword);
    // printf("%s\n", nextword);
    cursor = draw_word(cursor, y+line*vspacing, " ");
    if (current_len > line_len + 4) {
      current_len = 0;
      cursor = x;
      line++;
    }
    nextword = strtok (NULL, " ");

  }
}