#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "players.h"

void initialize_game(struct Player *players)
{
    char buzzer_keys[] = "qzpm";
    for (int i=0; i<4; ++i)  {
      attron(A_BOLD);
      printf("Please enter your name: ");
      attroff(A_BOLD);
      char name[100];
      fgets(name, 100, stdin);
      name[strlen(name)-1] = '\0';
      printf("Hello, %s! Your buzzer key is '%c'. Don't forget it!\n", name, buzzer_keys[i]);
      usleep(80000);
      strcpy(&players[i].name, name);
      players[i].score = 0; // Score to zero
      players[i].turn = false;
    }
    players[0].turn = true;
    usleep(300000);
    printf("Press the space bar to begin playing.\n");
    while (getchar() != ' ') usleep(5000);
}
