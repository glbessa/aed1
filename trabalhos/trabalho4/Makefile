CC = gcc
CFLAGS = -Wall -I$(IDIR) -g

CLIBS = -lm

IDIR = include
SRCDIR = src
SOURCES = $(SRCDIR)/*.c
BUILDDIR = build
EXE_NAME = main

SAVE_TESTS=valgrind_result

all: compile

compile: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(BUILDDIR)/$(EXE_NAME) $(CLIBS)

run: $(BUILDDIR)/$(EXE_NAME)
	./$(BUILDDIR)/$(EXE_NAME)

run-valgrind: $(BUILDDIR)/$(EXE_NAME)
	valgrind ./$(BUILDDIR)/$(EXE_NAME)

make test: $(BUILDDIR)/$(EXE_NAME)
	@echo -e "----------------- Test 1 -----------------\n\nVangrind result: $(SAVE_TESTS).1.txt\nInput file: test.1.txt"
	@valgrind --log-file=./$(SAVE_TESTS).1.txt ./$(BUILDDIR)/$(EXE_NAME) < test.1.txt
	@echo -e "\n\n------------------------------------------"

	@echo -e "----------------- Test 2 -----------------\n\nVangrind result: $(SAVE_TESTS).2.txt\nInput file: test.2.txt"
	@valgrind --log-file=./$(SAVE_TESTS).2.txt ./$(BUILDDIR)/$(EXE_NAME) < test.2.txt
	@echo -e "\n\n------------------------------------------"

	@echo -e "----------------- Test 3 -----------------\n\nVangrind result: $(SAVE_TESTS).3.txt\nInput file: test.3.txt"
	@valgrind --log-file=./$(SAVE_TESTS).3.txt ./$(BUILDDIR)/$(EXE_NAME) < test.3.txt
	@echo -e "\n\n------------------------------------------"