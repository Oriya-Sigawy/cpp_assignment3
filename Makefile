CC=g++
AR=ar 
FLAGS= -Wall -g -Wextra
HEADERS=Catan.hpp Board.hpp Player.hpp
.PHONY: all clean
all: frontend
test: testMain.o Catan.o Board.o Player.o
	$(CC) $(FLAGS) $^ -o test -lgcov
testMain.o: testMain.cpp Test.cpp
	$(CC) $(FLAGS) -c $< -o $@
frontend: Frontend.o Catan.o Board.o Player.o
	$(CC) $(FLAGS) $^ -o $@
Frontend.o: Frontend.cpp Frontend.hpp $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@
Catan.o: Catan.cpp $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@
Board.o: Board.cpp Board.hpp Player.hpp
	$(CC) $(FLAGS) -c $< -o $@ 
Player.o: Player.cpp Player.hpp
	$(CC) $(FLAGS) -c $< -o $@
clean:
	rm -f *.o frontend test