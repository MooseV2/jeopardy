
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LFLAGS = 
SOURCES = jeopardy.c questions.c players.c graphics.c utilities.c font.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = jeopardy
platform=$(shell uname)
ifeq ($(platform),Darwin)
LIBS = -lncurses
else
LIBS = -lncursesw
endif

.PHONY: clean help

jeopardy : jeopardy.o questions.o players.o utilities.o graphics.o font.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

all : $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~

cleanup:
	rm -f $(OBJECTS) *~

help:
	@echo "Valid targets:"
	@echo "  all:    generates all binary files"
	@echo "  clean:  removes .o and .exe files"
