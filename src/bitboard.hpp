#ifndef BITBOARDS_HPP
#define BITBOARDS_HPP

#include <stdint.h>
#include <iostream>
#include <cassert>
#include <sstream>
#include <iomanip>

class Bitboard {
public:
    Bitboard() : board(0) {}

    Bitboard(uint64_t board) : board(board) {}
    
    Bitboard setBit(int square) const {
        return Bitboard(board | (1ULL << square));
    }
    
    Bitboard clearBit(int square) const {
        return Bitboard(board & ~(1ULL << square));
    }

    uint64_t getBits() const { return board; }
    
    bool getBit(int square) {
        return (board & (1ULL << square)) != 0;
    }
    
    void print_bitboard() {
        for (int rank = 7; rank >= 0; --rank) {
            for (int file = 0; file < 8; ++file) {
                int square = rank * 8 + file;
                std::cout << (getBit(square) ? '1' : '0') << " ";
            }
            std::cout << std::endl;
        }
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
    std::string to_string() const {
        std::stringstream ss;
        for (int rank = 7; rank >= 0; --rank) {
            for (int file = 0; file < 8; ++file) {
                int square = rank * 8 + file;
                if ((board & (1ULL << square)) != 0) {
                    ss << "1";
                } else {
                    ss << "0";
                }
            }
            ss << "\n";
        }
        return ss.str();
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