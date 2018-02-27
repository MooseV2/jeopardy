#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "questions.h"
extern void draw_board(struct Player *players, struct Category *categories, bool double_jeopardy, struct Question **chosenQuestion);
extern void mvprintc(char *text, int cx, int cy, int offx, int offy);
#endif /* GRAPHICS_H */
