#include <iostream>
#include "chessboard.hpp"

int main() {
    ChessBoard board;
    board.initializeStartingBoard();
    board.printBoard();
    
    return 0;
}