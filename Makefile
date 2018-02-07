CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LFLAGS = 
LIBS = -lncurses
SOURCES = jeopardy.c questions.c players.c graphics.c utilities.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = jeopardy
.PHONY: clean help

jeopardy : jeopardy.o questions.o players.o utilities.o graphics.o
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
