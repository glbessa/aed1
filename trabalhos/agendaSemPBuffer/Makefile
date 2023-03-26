NAME=agenda
SAVE_TESTS=valgrind_result
COMPILER=gcc
COMPILER_ARGS=-Wall -lm -g -o $(NAME)

VALGRIND_ARGS=-s --track-origins=yes --leak-check=full --show-leak-kinds=all

make compile: $(NAME).c
	$(COMPILER) $(COMPILER_ARGS) $(NAME).c

make run: $(NAME)
	./$(NAME)

make run-with-valgrind:
	valgrind $(VALGRIND_ARGS) ./$(NAME)

make test: $(NAME)
	@echo -e "----------------- Test 1 -----------------\n\nVangrind result: $(SAVE_TESTS).1.txt\nInput file: test.1.txt"
	@valgrind $(VALGRIND_ARGS) --log-file=./$(SAVE_TESTS).1.txt ./$(NAME) < test.1.txt > test.1.output.txt
	@echo -e "\n\n------------------------------------------"

	@echo -e "----------------- Test 2 -----------------\n\nVangrind result: $(SAVE_TESTS).2.txt\nInput file: test.2.txt"
	@valgrind $(VALGRIND_ARGS) --log-file=./$(SAVE_TESTS).2.txt ./$(NAME) < test.2.txt > test.2.output.txt
	@echo -e "\n\n------------------------------------------"

	@echo -e "----------------- Test 3 -----------------\n\nVangrind result: $(SAVE_TESTS).3.txt\nInput file: test.3.txt"
	@valgrind $(VALGRIND_ARGS) --log-file=./$(SAVE_TESTS).3.txt ./$(NAME) < test.3.txt > test.3.output.txt
	@echo -e "\n\n------------------------------------------"