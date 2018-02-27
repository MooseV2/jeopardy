#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "questions.h"
#include "utilities.h"
extern void draw_board(struct Player *players, struct Category *categories, struct Question **chosenQuestion);
extern void mvprintc(char *text, int cx, int cy, int offx, int offy);
extern void draw_rectangle(int y1, int x1, int y2, int x2);
extern bool request_answer(struct Player player, struct Question *question);
extern int draw_question_board(struct Question *question, struct Player *player_list, int n_players, int *already_buzzed);
#endif /* GRAPHICS_H */
