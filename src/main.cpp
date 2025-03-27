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

    // Square pawnSquare = e4;
    // PieceColour pawnColour = WHITE;
    // Bitboard pawnMoves = moveGen.maskPawnAttacks(pawnColour, pawnSquare);

    // Square knightSquare = a1;
    // Bitboard knightMoves = moveGen.maskKnightAttacks(knightSquare);

    Square kingSquare = e4;
    Bitboard kingMoves = moveGen.maskKingAttacks(kingSquare);

    kingMoves.printBitboard();

    // for (int square = 0; square < 64; ++square) {
    //     std::cout << square << std::endl;
    //     Bitboard pawnAttacks = moveGen.getPawnAttacks(BLACK, square);
    //     pawnAttacks.printBitboard();
    // }

    return 0;
}