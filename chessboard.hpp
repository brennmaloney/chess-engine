#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "bitboard.hpp"
#include <stdint.h>
#include <iostream>


enum PieceType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    NO_PIECE
};

enum PieceColour {
    WHITE,
    BLACK,
    NO_COLOUR
};

class ChessBoard {
public:
    ChessBoard() : turn(WHITE), castlingRights(0xF), enPassantSquare(-1), halfMoveClock(0), fullMoveNumber(1) {

    }

    void initializeStartingBoard() {
        whitePawns = Bitboard(0x00FF000000000000ULL);
        whiteKnights = Bitboard(0x4200000000000000ULL);
        whiteBishops = Bitboard(0x2400000000000000ULL);
        whiteRooks = Bitboard(0x8100000000000000ULL);
        whiteQueens = Bitboard(0x0800000000000000ULL);
        whiteKings = Bitboard(0x1000000000000000ULL);

        blackPawns = Bitboard(0x000000000000FF00ULL);
        blackKnights = Bitboard(0x0000000000000042ULL);
        blackBishops = Bitboard(0x0000000000000024ULL);
        blackRooks = Bitboard(0x0000000000000081ULL);
        blackQueens = Bitboard(0x0000000000000008ULL);
        blackKings = Bitboard(0x0000000000000010ULL);
    }

    void printBoard() {
        for (int rank = 7; rank >= 0; --rank) {
            for (int file = 0; file < 8; ++file) {
                int square = rank * 8 + file;
                PieceType piece = getPieceAtSquare(square);
                PieceColour colour = getColourAtSquare(square);
                char pieceChar = '.';
                if (piece != NO_PIECE) {
                    if (colour != WHITE) {
                        pieceChar = "PNBRQK"[piece];
                    } else {
                        pieceChar = "pnbrqk"[piece];
                    }
                }
                std::cout << pieceChar << " ";
            }
            std::cout << std::endl;
        }
    }

    PieceType getPieceAtSquare(int square) const {
        Bitboard squareBoard = Bitboard(1ULL << square);
        if ((whitePawns & squareBoard).popCount() == 1) return PAWN;
        if ((whiteKnights & squareBoard).popCount() == 1) return KNIGHT;
        if ((whiteBishops & squareBoard).popCount() == 1) return BISHOP;
        if ((whiteRooks & squareBoard).popCount() == 1) return ROOK;
        if ((whiteQueens & squareBoard).popCount() == 1) return QUEEN;
        if ((whiteKings & squareBoard).popCount() == 1) return KING;
        if ((blackPawns & squareBoard).popCount() == 1) return PAWN;
        if ((blackKnights & squareBoard).popCount() == 1) return KNIGHT;
        if ((blackBishops & squareBoard).popCount() == 1) return BISHOP;
        if ((blackRooks & squareBoard).popCount() == 1) return ROOK;
        if ((blackQueens & squareBoard).popCount() == 1) return QUEEN;
        if ((blackKings & squareBoard).popCount() == 1) return KING;
        return NO_PIECE;
    }

    PieceColour getColourAtSquare(int square) const{
        Bitboard squareBoard = Bitboard(1ULL << square);
        if (((whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKings) & squareBoard).popCount() == 1) return WHITE;
        if (((blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKings) & squareBoard).popCount() == 1) return BLACK;
        return NO_COLOUR;
    }

    void placePiece(PieceType piece, PieceColour color, int square){
        Bitboard squareBoard = Bitboard(1ULL << square);
        if(color == WHITE){
            if(piece == PAWN) whitePawns = whitePawns | squareBoard;
            if(piece == KNIGHT) whiteKnights = whiteKnights | squareBoard;
            if(piece == BISHOP) whiteBishops = whiteBishops | squareBoard;
            if(piece == ROOK) whiteRooks = whiteRooks | squareBoard;
            if(piece == QUEEN) whiteQueens = whiteQueens | squareBoard;
            if(piece == KING) whiteKings = whiteKings | squareBoard;
        }
        if(color == BLACK){
            if(piece == PAWN) blackPawns = blackPawns | squareBoard;
            if(piece == KNIGHT) blackKnights = blackKnights | squareBoard;
            if(piece == BISHOP) blackBishops = blackBishops | squareBoard;
            if(piece == ROOK) blackRooks = blackRooks | squareBoard;
            if(piece == QUEEN) blackQueens = blackQueens | squareBoard;
            if(piece == KING) blackKings = blackKings | squareBoard;
        }
    }

    void removePiece(int square){
        Bitboard squareBoard = Bitboard(1ULL << square);
        whitePawns = whitePawns & (~squareBoard);
        whiteKnights = whiteKnights & (~squareBoard);
        whiteBishops = whiteBishops & (~squareBoard);
        whiteRooks = whiteRooks & (~squareBoard);
        whiteQueens = whiteQueens & (~squareBoard);
        whiteKings = whiteKings & (~squareBoard);
        blackPawns = blackPawns & (~squareBoard);
        blackKnights = blackKnights & (~squareBoard);
        blackBishops = blackBishops & (~squareBoard);
        blackRooks = blackRooks & (~squareBoard);
        blackQueens = blackQueens & (~squareBoard);
        blackKings = blackKings & (~squareBoard);
    }

private:
    Bitboard whitePawns;
    Bitboard whiteKnights;
    Bitboard whiteBishops;
    Bitboard whiteRooks;
    Bitboard whiteQueens;
    Bitboard whiteKings;

    Bitboard blackPawns;
    Bitboard blackKnights;
    Bitboard blackBishops;
    Bitboard blackRooks;
    Bitboard blackQueens;
    Bitboard blackKings;

    PieceColour turn;
    uint8_t castlingRights;
    int enPassantSquare;
    int halfMoveClock;
    int fullMoveNumber;
};


#endif