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


void load_questions(struct Question *questions) {
    strcpy(&questions[0].category,"WTF IS THIS BULLSHIT");
    strcpy(&questions[0].question,"TheQuestion");
    strcpy(&questions[0].answer, "aa");
    questions[0].value = 100;
    questions[0].answered = false;
    
}

bool answerQuestion(struct Question *question) {
    printf("Question: %s\n", question->question);
    printf("What is your answer? ");
    char answer[MAX_LEN];
    fgets(answer, MAX_LEN, stdin);
    answer[strlen(answer)-1] = '\0';
    printf("You answered '%s'\n", answer);
    if (!strcmp(answer, question->answer)) {
        printf("That's fucking right mate.\n");
        return true;
    } else {
        printf("Nope.\n");
        return false;
    }
    
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}
