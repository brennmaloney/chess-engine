CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

all: chess_engine

chess_engine: main.o
	$(CXX) $(CXXFLAGS) main.o -o chess_engine

main.o: main.cpp bitboard.hpp chessboard.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f chess_engine *.o