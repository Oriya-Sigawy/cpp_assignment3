CC=g++
AR=ar 
FLAGS= -Wall -g -Wextra
HEADERS=Catan.hpp Board.hpp Player.hpp
OBJECTS=Catan.o Board.o Player.o
.PHONY: all clean
all: frontend
main: main.o $(OBJECTS)
	$(CC) $(FLAGS) $^ -o main
main.o: Main.cpp
	$(CC) $(FLAGS) -c $< -o $@
test: testMain.o $(OBJECTS)
	$(CC) $(FLAGS) $^ -o test -lgcov
testMain.o: testMain.cpp Test.cpp
	$(CC) $(FLAGS) -c $< -o $@
frontend: Frontend.o $(OBJECTS)
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
	rm -f *.o frontend test main