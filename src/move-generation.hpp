#ifndef MOVEGENERATION_HPP
#define MOVEGENERATION_HPP

#include "chessboard.hpp"
#include <stdint.h>
#include <iostream>
#include <vector>


class MoveGeneration {
public:
    MoveGeneration(const ChessBoard& board) : board_(board) {
        initMoveMasks();
        initLeaperAttacks();
    }

    // board masks
    void initMoveMasks() {
        notAFile = Bitboard(0xfefefefefefefefeULL);
        notABFile = Bitboard(0xfcfcfcfcfcfcfcfcULL);
        notHFile = Bitboard(0x7f7f7f7f7f7f7f7fULL);
        notGHFile = Bitboard(0x3f3f3f3f3f3f3f3fULL);
    }

    void initLeaperAttacks() {
        for (int square = 0; square < 64; ++square) {
            pawnAttacks[WHITE][square] = maskPawnAttacks(WHITE, square);
            pawnAttacks[BLACK][square] = maskPawnAttacks(BLACK, square);
        }
    }

    // getters/setters
    Bitboard getPawnAttacks(PieceColour colour, int square) const {
        return pawnAttacks[colour][square];
    }

    Bitboard maskPawnAttacks(PieceColour colour, int square) {
        Bitboard attacks = Bitboard(0ULL);
        Bitboard board = Bitboard(1ULL << square);

        if (colour == WHITE) {
            if (((board >> 7) & notAFile).popCount() > 0) attacks |= (board >> 7);
            if (((board >> 9) & notHFile).popCount() > 0) attacks |= (board >> 9);
        } else {
            if (((board << 7) & notHFile).popCount() > 0) attacks |= (board << 7);
            if (((board << 9) & notAFile).popCount() > 0) attacks |= (board << 9);
        }

        return attacks;
    }

private:
    const ChessBoard& board_;

    Bitboard pawnAttacks[2][64];

    Bitboard notAFile;
    Bitboard notABFile;
    Bitboard notHFile;
    Bitboard notGHFile;
};


#endif