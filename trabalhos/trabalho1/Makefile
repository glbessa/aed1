NOME=climbingStairs
SAVE_TESTS=valgrind_result

make all: $(NOME).c
	gcc -Wall -g -o $(NOME) $(NOME).c

make run: $(NOME)
	./$(NOME)

make test: $(NOME)
	@echo -e "----------------- Test 1 -----------------\n\nVangrind result: $(SAVE_TESTS).1.txt\nInput file: test.1.txt"
	@valgrind --log-file=./$(SAVE_TESTS).1.txt ./$(NOME) < test.1.txt
	@echo -e "\n\n------------------------------------------"

	@echo -e "----------------- Test 2 -----------------\n\nVangrind result: $(SAVE_TESTS).2.txt\nInput file: test.2.txt"
	@valgrind --log-file=./$(SAVE_TESTS).2.txt ./$(NOME) < test.2.txt
	@echo -e "\n\n------------------------------------------"

	@echo -e "----------------- Test 3 -----------------\n\nVangrind result: $(SAVE_TESTS).3.txt\nInput file: test.3.txt"
	@valgrind --log-file=./$(SAVE_TESTS).3.txt ./$(NOME) < test.3.txt
	@echo -e "\n\n------------------------------------------"