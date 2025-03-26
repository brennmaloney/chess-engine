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
    board.printBoard();

    MoveGeneration moveGen(board);
    // int pawnSquare = 17;
    // PieceColour pawnColour = BLACK;

    // Bitboard pawnMoves = moveGen.maskPawnAttacks(pawnColour, pawnSquare);

    // pawnMoves.printBitboard();

    std::cout.flush();
    for (int square = 0; square < 64; ++square) {
        std::cout << square << std::endl;
        Bitboard pawnAttacks = moveGen.getPawnAttacks(BLACK, square);
        pawnAttacks.printBitboard();
    }

    return 0;
}