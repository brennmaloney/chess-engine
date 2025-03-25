#include "chessboard.hpp"
#include "move-generation.hpp"
#include <iostream>
#include <vector>

std::string pieceColourToString(PieceColour colour) {
    if (colour == WHITE) return "WHITE";
    if (colour == BLACK) return "BLACK";
    if (colour == NO_COLOUR) return "NO_COLOUR";
    return "UNKNOWN";
}

int main() {
    ChessBoard board;
    board.initializeStartingBoard();
    board.printBoard();
    
    return 0;
}