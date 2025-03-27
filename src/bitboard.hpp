#ifndef BITBOARDS_HPP
#define BITBOARDS_HPP

#include <stdint.h>
#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

enum Square {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

class Bitboard {
public:
    Bitboard() : board(0) {}

    Bitboard(uint64_t board) : board(board) {}
    
    Bitboard clearBit(Square square) const {
        return Bitboard(board & ~(1ULL << square));
    }

    Bitboard setBit(Square square) const {
        return Bitboard(board | (1ULL << square));
    }
    bool getBit(Square square) {
        return (board & (1ULL << square)) != 0;
    }
    uint64_t getBits() const { return board; }
    int popBit() {
        if (!board) {
            return -1;
        }
        int square = bitScanForward();
        board &= board - 1;
        return square;
    }
    
    void printBitboard() {
        std::cout << "\nPrint Bitboard" << std::endl;
        for (int rank = 0; rank < 8; ++rank) {
            for (int file = 0; file < 8; ++file) {
                Square square = static_cast<Square>(rank * 8 + file);

                if (!file) {
                    std::cout << 8 - rank << "    ";
                }

                std::cout << (getBit(square) ? '1' : '0') << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n     a b c d e f g h" << std::endl;
    }
    
    // Brian Kernighan's way
    // reset LS1B until bitset becomes empty
    int popCount(){
        uint64_t tempBoard = board;
        int count = 0;
        while(tempBoard){
            count++;
            tempBoard &= tempBoard - 1; // reset LS1B
        }
        return count;
    }
    
    // De Bruijn Multiplication
    int bitScanForward() {
        const uint64_t debruijn64 = 0x03f79d71b4cb0a89ULL;
        assert (board != 0);
        const int index64[64] = {
            0,  1, 48,  2, 57, 49, 28,  3,
            61, 58, 50, 42, 38, 29, 17,  4,
            62, 55, 59, 36, 53, 51, 43, 22,
            45, 39, 33, 30, 24, 18, 12,  5,
            63, 47, 56, 27, 60, 41, 37, 16,
            54, 35, 52, 21, 44, 32, 23, 11,
            46, 26, 40, 15, 34, 20, 31, 10,
            25, 14, 19,  9, 13,  8,  7,  6
        };
        return index64[((board & -board) * debruijn64) >> 58];
    }

    Bitboard operator&(const Bitboard& other) const {
        return Bitboard(board & other.board);
    }

    Bitboard operator|(const Bitboard& other) const {
        return Bitboard(board | other.board);
    }

    Bitboard operator|=(const Bitboard& other) {
        board |= other.board;
        return *this;
    }

    Bitboard operator^(const Bitboard& other) const {
        return Bitboard(board ^ other.board);
    }

    Bitboard operator<<(int shift) const {
        return Bitboard(board << shift);
    }

    Bitboard operator>>(int shift) const {
        return Bitboard(board >> shift);
    }
    Bitboard operator~() const {
        return Bitboard(~board);
    }
private:
    uint64_t board;
};

#endif