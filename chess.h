#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <vector>
#include <string>

// Represents a single chess piece
struct Piece {
    char symbol;   // 'K', 'Q', 'R', 'B', 'N', 'P' (uppercase = White, lowercase = Black)
    bool isWhite;
    bool isEmpty;  // true if the square has no piece
};

// Manages the board state and game logic
class ChessBoard {
public:
    ChessBoard();
    void display() const;
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol, bool whiteTurn);
    bool kingCaptured() const;   // Returns true if a king was just captured

private:
    Piece board[8][8];
    bool wasCaptured;            // Tracks if a king was captured
    void initBoard();
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, bool whiteTurn) const;
};

#endif
