CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -Isrc

SRCS = src/main.cpp

all: build/chess_engine

build/chess_engine: build/main.o
	$(CXX) $(CXXFLAGS) build/main.o -o build/chess_engine

build/%.o: src/%.cpp src/bitboard.hpp src/chessboard.hpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build *.o

.PHONY: all clean