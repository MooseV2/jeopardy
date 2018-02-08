#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "players.h"

void initialize_game(struct Player *players)
{
    for (int i=0; i<4; ++i)  {
      printf("Please enter your name: ");
      char name[100];
      fgets(name, 100, stdin);
      name[strlen(name)-1] = '\0';
      
      strcpy(&players[i].name, name);
      players[i].score = 0; // Score to zero
      players[i].turn = false;
    }
    players[0].turn = true;
}

void draw_scoreboard(struct Player *players) {
  struct Player *ptr = players;
  for (int i=0; i<4; i++) { //REFACTOR
     printf("Name: %s\tScore:%d\n", &ptr->name, ptr->score);
    ptr++;
  }

}