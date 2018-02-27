/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#ifndef QUESTIONS_H_
#define QUESTIONS_H_

#include <stdbool.h>

#define MAX_LEN 256
#define NUM_CATEGORIES 6
#define NUM_Q_PER_CATEGORY 5
// The number of questions, you can use this in your functions in
// questions.c, this can be accessed in questions.c
#define NUM_QUESTIONS 36

// Questions struct for each question
struct Question {
    char question[MAX_LEN];
    char answer[MAX_LEN];
    int value;
    bool answered;
};

struct Category {
    char name[MAX_LEN];
    struct Question questions[NUM_Q_PER_CATEGORY];
};

extern struct Category* load_questions(char *filename);
#endif /* QUESTIONS_H_ */