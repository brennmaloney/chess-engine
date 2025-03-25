#ifndef MOVEGENERATION_HPP
#define MOVEGENERATION_HPP

#include "chessboard.hpp"
#include <stdint.h>
#include <iostream>
#include <vector>


class MoveGeneration {
public:
    MoveGeneration(const ChessBoard& board) : board_(board){}

    std::vector<int> pawnMoveGenerator(int square, PieceColour colour) {
        std::vector<int> moves;
        int rank = square / 8;
        int file = square % 8;
        int direction = (colour  == WHITE) ? 1 : -1;

        int pushSquare = square + 8 * direction;
        if (rank + direction >= 0 && rank + direction < 8 && board_.getPieceAtSquare(pushSquare) == NO_PIECE) {
            moves.push_back(pushSquare);
            if((colour == WHITE && rank == 1) || (colour == BLACK && rank == 6)) {
                int doublePushSquare = square + 16 * direction;
                if (board_.getPieceAtSquare(doublePushSquare) == NO_PIECE) {
                    moves.push_back(doublePushSquare);
                }
            }
        }

        // check captures on left
        int captureLeftSquare = square + 7 * direction;
        if (rank + direction >= 0 && rank + direction < 8 && file > 0 && board_.getPieceAtSquare(captureLeftSquare) != NO_PIECE && board_.getColourAtSquare(captureLeftSquare) != colour) {
            moves.push_back(captureLeftSquare);
        }
        // check captures on right
        int captureRightSquare = square + 9 * direction;
        if (rank + direction >= 0 && rank + direction < 8 && file < 7 && board_.getPieceAtSquare(captureRightSquare) != NO_PIECE && board_.getColourAtSquare(captureRightSquare) != colour) {
            moves.push_back(captureRightSquare);
        }

        if (board_.getEnPassantSquare() != -1) {
            if (rank == ((colour == WHITE) ? 4 : 3)) {
                if (file > 0 && square + 7 * direction == board_.getEnPassantSquare()) {
                    moves.push_back(square + 7 * direction);
                }
                if  (file < 7 && square + 9 * direction == board_.getEnPassantSquare()) {
                    moves.push_back(square + 9 * direction);
                }
            }
        }

        return moves;
    }

private:
    const ChessBoard& board_;

};


#endif