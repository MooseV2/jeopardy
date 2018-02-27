/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2018, Anthony DeSouza
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <ncurses.h>
#include <signal.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"
#include "graphics.h"
#include "sound.h"
#include "font.h"
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

#include "utilities.h"
int main() {
    pid_t audio = fork();
    if (audio == 0) { // Child
        play("Jeopardy.aiff");
        exit(0);
    }
    struct Player players[NUM_PLAYERS];
    initialize_game(&players);
    whaddup_trebek();
    usleep(300000);
    printf("Press the enter to begin playing.\n");
    getchar();
    struct Category *categories;
    categories = load_questions("questions.txt");
    struct Question *chosenQuestion;
    int nQuestions = 5*6;
    int already_pressed = 0;
    struct Player *player_turn = &players[0];

    while (nQuestions--) {
        draw_board(&players, categories, false, &chosenQuestion);
        
        while (true) {
            int result = draw_question_board(chosenQuestion, &players, NUM_PLAYERS, &already_pressed);
            if (result == -1) { // No one answered
                char preface[] = "The correct answer is ";
                char *failure = calloc(strlen(preface) + strlen(chosenQuestion->answer), sizeof(char));
                strcpy(failure, preface);
                strcpy(failure + strlen(preface), chosenQuestion->answer);
                refresh();
                draw_billboard(failure, 5);
                refresh();
                timeout(7000);
                getch();
                chosenQuestion->answered=true;
                already_pressed = 0;
                break;
            }
            bool correct = request_answer(players[result], chosenQuestion);
            if (correct) {
                chosenQuestion->answered=true;
                players[result].score += chosenQuestion->value;
                player_turn->turn = false;
                player_turn = &players[result];
                player_turn->turn = true;
                
                break;
            } else {
                players[result].score -= chosenQuestion->value;
            }
            clear();
            refresh();
        }
        already_pressed = 0;
    }
    struct Player winner = players[0];
    for (int i=1; i<NUM_PLAYERS; ++i) {
        winner = winner.score > players[i].score ? winner : players[i];
    }
    char winner_text[300];
    sprintf(&winner_text, "The winner is %s with %d dollars", winner.name, winner.score);
    char typewriter[300] = {0};
    for (int i=0; i<strlen(winner_text); i++) {
        char c = winner_text[i];
        typewriter[strlen(typewriter)] = c;
        draw_billboard(typewriter, 5);
        refresh();
        usleep(50000);
    }
    timeout(30000);
    getch();
    kill(audio, SIGUSR1);
    endwin();
    return 0;
}