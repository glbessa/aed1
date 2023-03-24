CC = gcc
CFLAGS = -Wall -I$(IDIR) -g

IDIR = ./include/
SRCDIR = ./src/
SOURCES = $(SRCDIR)*.c
EXE_NAME = exempleStack

all: compile

compile: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXE_NAME)

run:
	./$(EXE_NAME)