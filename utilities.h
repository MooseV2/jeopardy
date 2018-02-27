#ifndef UTILITIES_H
#define UTILITIES_H
#include <stdbool.h>
// Player struct for each player
struct Player {
    char name[256];
    int score;
    bool turn;
    char buzzer;
};

// Initializes the array of questions for the game
extern void initialize_game(struct Player *players);
extern bool verify_answer(char *real_answer, char *given_answer);
extern void whaddup_trebek();
#endif /* UTILITIES_H */