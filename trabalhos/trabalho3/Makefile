CC = gcc
CFLAGS = -Wall -I$(IDIR) -g

IDIR = ./include/
SRCDIR = ./src/
SOURCES = $(SRCDIR)*.c
EXE_NAME = main

SAVE_TESTS=valgrind_result

all: compile

compile: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXE_NAME)

run: $(EXE_NAME)
	./$(EXE_NAME)

run-valgrind: $(EXE_NAME)
	valgrind ./$(EXE_NAME)

make test: $(EXE_NAME)
	@echo -e "----------------- Test 1 -----------------\n\nVangrind result: $(SAVE_TESTS).1.txt\nInput file: test.1.txt"
	@valgrind --log-file=./$(SAVE_TESTS).1.txt ./$(EXE_NAME) < test.1.txt
	@echo -e "\n\n------------------------------------------"

	@echo -e "----------------- Test 2 -----------------\n\nVangrind result: $(SAVE_TESTS).2.txt\nInput file: test.2.txt"
	@valgrind --log-file=./$(SAVE_TESTS).2.txt ./$(EXE_NAME) < test.2.txt
	@echo -e "\n\n------------------------------------------"

	@echo -e "----------------- Test 3 -----------------\n\nVangrind result: $(SAVE_TESTS).3.txt\nInput file: test.3.txt"
	@valgrind --log-file=./$(SAVE_TESTS).3.txt ./$(EXE_NAME) < test.3.txt
	@echo -e "\n\n------------------------------------------"