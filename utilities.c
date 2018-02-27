/*
 * Jeopardy
 *
 * Copyright (C) 2018, Anthony DeSouza
 * All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include "utilities.h"

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

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
      players[i].buzzer = buzzer_keys[i];
      players[i].score = 0; // Score to zero
      players[i].turn = false;
    }
    players[0].turn = true;
    
}

int levenshtein(char *s1, char *s2) {
    unsigned int x, y, s1len, s2len;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++)
            matrix[x][y] = MIN3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));

    return(matrix[s2len][s1len]);
}

// Ensures the answer has its interrogative (what is/who are/etc)
#define IS(a,b) (strcmp(a,b)==0) 
bool verify_interrogative(char **str) {
    char *word = strtok(*str, " "); // First word
    if (!(IS(word, "who") || IS(word, "what") || IS(word, "where") || IS(word, "when") || IS(word, "why") || IS(word, "how")))
        return false;
    word = strtok(NULL, " ");
    if (!(IS(word, "is") || IS(word, "are")))
        return false;
    word = strtok(NULL, "");
    *str = word;
    return true;
}

#define lower(str) for (int i = 0; i < (int)strlen(str); i++) str[i] = tolower(str[i]);
bool verify_answer(char *real_answer, char *given_answer) {
    if (strlen(given_answer) == 0) return false;
    lower(real_answer);
    lower(given_answer);
    if (!verify_interrogative(&given_answer)) return false;
    int dist = levenshtein(real_answer, given_answer);
    return (dist < 2);
}

void whaddup_trebek() {
    int fd = open("trebek_small", O_RDONLY);
    char buf[1024];
    int buflen;
    while((buflen = read(fd, buf, 1024)) > 0)
    {
        write(1, buf, buflen);
    }
    close(fd);
}