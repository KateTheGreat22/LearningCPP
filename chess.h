#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <vector>
#include <string>

// Holds data for a single chess piece
struct Piece {
    char symbol;   // Uppercase = White, lowercase = Black (K, Q, R, B, N, P)
    bool isWhite;
    bool isEmpty;  // True if no piece is on this square
};

// Handles board setup, display, and move logic
class ChessBoard {
public:
    ChessBoard();
    void display() const;         // Prints the current board to the terminal
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol, bool whiteTurn);
    bool kingCaptured() const;    // Returns true if a king was taken

private:
    Piece board[8][8];            // 8x8 grid storing all piece data
    bool wasCaptured;             // Flips to true when a king is captured
    void initBoard();             // Sets up starting positions
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, bool whiteTurn) const;
};

#endif
