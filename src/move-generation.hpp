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


    // --------- start initialization ---------
    void initMoveMasks() {
        notAFile = Bitboard(0xfefefefefefefefeULL);
        notABFile = Bitboard(0xfcfcfcfcfcfcfcfcULL);
        notHFile = Bitboard(0x7f7f7f7f7f7f7f7fULL);
        notGHFile = Bitboard(0x3f3f3f3f3f3f3f3fULL);
    }

    void initLeaperAttacks() {
        for (int square = 0; square < 64; ++square) {
            // initialize pawn attacks
            pawnAttacks[WHITE][square] = maskPawnAttacks(WHITE, static_cast<Square>(square));
            pawnAttacks[BLACK][square] = maskPawnAttacks(BLACK, static_cast<Square>(square));

            // initialize knight attacks
            knightAttacks[square] = maskKnightAttacks(static_cast<Square>(square));

            // initialize king attacks
            kingAttacks[square] = maskKingAttacks(static_cast<Square>(square));
        }
    }
    // --------- end initialization ---------



    // -------- start getters/setters ----------
    // example for pawnAttacks
    // pawnAttacks[WHITE][d4]
    // . . . . . . . .
    // . . . . . . . .
    // . . . . . . . .
    // . . 1 . 1 . . .
    // . . . . . . . .
    // . . . . . . . .
    // . . . . . . . .
    // . . . . . . . .
    Bitboard getPawnAttacks(PieceColour colour, Square square) const {
        return pawnAttacks[colour][square];
    }

    // example for knightAttacks
    // knightAttacks[d4]
    // . . . . . . . .
    // . . . . . . . .
    // . . 1 . 1 . . .
    // . 1 . . . 1 . .
    // . . . . . . . .
    // . 1 . . . 1 . .
    // . . 1 . 1 . . .
    // . . . . . . . .
    Bitboard getKnightAttacks(Square square) const {
        return knightAttacks[square];
    }

    // example for kingAttacks
    // kingAttacks[d4]
    // . . . . . . . .
    // . . . . . . . .
    // . . . . . . . .
    // . . 1 1 1 . . .
    // . . 1 . 1 . . .
    // . . 1 1 1 . . .
    // . . . . . . . .
    // . . . . . . . .
    Bitboard getKingAttacks(Square square) const {
        return kingAttacks[square];
    }
    // --------- end getters/setters ---------



    // -------- generators for attacks ----------
    Bitboard maskPawnAttacks(PieceColour colour, Square square) {
        Bitboard attacks = Bitboard(0ULL);
        Bitboard board = Bitboard(1ULL << square);

        if (colour == WHITE) {
            attacks |= (board >> 7) & notAFile;
            attacks |= (board >> 9) & notHFile;
        } else {
            attacks |= (board << 7) & notHFile;
            attacks |= (board << 9) & notAFile;
        }

        return attacks;
    }

    Bitboard maskKnightAttacks(Square square) {
        Bitboard attacks = Bitboard(0ULL);
        Bitboard board = Bitboard(1ULL << square);

        attacks |= (board >> 17) & notHFile;
        attacks |= (board >> 15) & notAFile;
        attacks |= (board >> 10) & notGHFile;
        attacks |= (board >> 6) & notABFile;
        attacks |= (board << 17) & notAFile;
        attacks |= (board << 15) & notHFile;
        attacks |= (board << 10) & notABFile;
        attacks |= (board << 6) & notGHFile;

        return attacks;
    }

    Bitboard maskKingAttacks(Square square) {
        Bitboard attacks = Bitboard(0ULL);
        Bitboard board = Bitboard(1ULL << square);

        attacks |= (board >> 9) & notHFile;
        attacks |= (board >> 8);
        attacks |= (board >> 7) & notAFile;
        attacks |= (board >> 1) & notHFile;
        attacks |= (board << 9) & notAFile;
        attacks |= (board << 8);
        attacks |= (board << 7) & notHFile;
        attacks |= (board << 1) & notAFile;

        return attacks;
    }
    // -------- end generators for attacks ----------


private:
    const ChessBoard& board_;

    Bitboard pawnAttacks[2][64];
    Bitboard knightAttacks[64];
    Bitboard kingAttacks[64];

    Bitboard notAFile;
    Bitboard notABFile;
    Bitboard notHFile;
    Bitboard notGHFile;
};


#endif