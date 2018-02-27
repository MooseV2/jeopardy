/*
 * Jeopardy
 *
 * Copyright (C) 2018, Anthony DeSouza
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#define STRIP_NL(x) x[strlen(x)-1]='\0'

struct Category* load_questions(char *filename) {
    FILE *questionFile = fopen(filename, "r");

    if (questionFile == NULL) {
        perror("Can't find questions file!");
        exit(1);
    }
    char line[256];
    // Get number of categories
    fgets(line, sizeof(line), questionFile);
    int nCategories = atoi(line);
    struct Category *categories = (struct Category*)malloc(nCategories * sizeof(struct Category));
    for (int c=0; c<nCategories; ++c) {
        // Category name
        fgets(categories[c].name, 256, questionFile);
        STRIP_NL(categories[c].name);
        for (int i=0; i<5; i++) { //Five questions
            fgets(line, sizeof(line), questionFile);
            STRIP_NL(line);
            char *split = strtok(line, "#");
            strcpy(categories[c].questions[i].question, split);
            split = strtok(NULL, "#");
            strcpy(categories[c].questions[i].answer, split); // Next value
            categories[c].questions[i].value = 200*(1+i);
        }
    }
    fclose(questionFile);
    return categories;
}