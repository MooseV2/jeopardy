/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"
#include "graphics.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

#include "utilities.h"

// Put global environment variables here

// Displays the game results for each player, their name and final score, ranked from first to last place
//void show_results(struct Player *players, int num_players);

int game_state;

int buzzedin() {
    // This function is not kosher
    // Please replace
    // Pretty please
    char playerName[10];
    printf("Who buzzed in?\n");
    fgets(playerName, 10, stdin);
    playerName[strlen(playerName)-1] = '\0';
    return atoi(playerName);
}

// int notmain(int argc, char *argv[])
// {
//     // An array of 4 players, may need to be a pointer if you want it set dynamically
    
//     struct Question questions[2];
//     // Buffer for user input

//     // Display the game introduction and initialize the questions
    
    
//     printf("%s: %d\n", players[0].name, players[1].score);
//     updateScore(&players[1], 200);
//     printf("%s: %d\n", players[0].name, players[1].score);
    
//     draw_scoreboard(&players);
    
//     load_questions(&questions);

//     printf("Question:\n\tQ:%s\n\tA:%s\n\tC:%s\n\tV:%d\n\tanswered:%d\n", 
//     questions[0].question,
//     questions[0].answer,
//     questions[0].category,
//     questions[0].value,
//     questions[0].answered);

    
//     while (true) {
//         struct Player thePlayer = players[buzzedin()];
//         printf("Player %s is answering (current score: %d).\n", thePlayer.name, thePlayer.score);
        
//         struct Question question = questions[0];
//         bool correct = answerQuestion(&question);
//         // Returns true or false; if false, other player can answer
//         if (correct) {
//             updateScore(&thePlayer, question.value);
//             break;
//         } else {
//             updateScore(&thePlayer, -question.value);
//         }
//     }
    
//     return EXIT_SUCCESS;
// }

int main() {
    struct Player players[NUM_PLAYERS];
    initialize_game(&players);
    struct Category *categories;
    categories = load_questions("questions.txt");
    categories[0].questions[1].answered=true;
    struct Question *chosenQuestion;
    int nQuestions = 5*6;
    while (nQuestions--) {
        draw_board(&players, categories, false, &chosenQuestion);
        draw_question_board(chosenQuestion);
        
        chosenQuestion->answered=true;
    }
    // print_categories(categories, 0, 0);
    return 0;
}