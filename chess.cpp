#include "chess.h"

// Initialize wasCaptured and set up the board
ChessBoard::ChessBoard() {
    wasCaptured = false;
    initBoard();
}

// Place all pieces in standard chess starting positions
void ChessBoard::initBoard() {
    char backRow[8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};

    for (int col = 0; col < 8; col++) {
        // Black back row uses lowercase symbols
        board[0][col] = {(char)tolower(backRow[col]), false, false};
        board[1][col] = {'p', false, false};

        // Middle rows start empty
        for (int row = 2; row <= 5; row++) {
            board[row][col] = {' ', false, true};
        }

        // White pieces on rows 6 and 7
        board[6][col] = {'P', true, false};
        board[7][col] = {backRow[col], true, false};
    }
}

// Print the board with column letters and row numbers
void ChessBoard::display() const {
    std::cout << "\n    a  b  c  d  e  f  g  h\n";
    std::cout << "   ------------------------\n";

    for (int row = 0; row < 8; row++) {
        // 8 - row flips the index so row 0 displays as 8
        std::cout << (8 - row) << " | ";

        for (int col = 0; col < 8; col++) {
            if (board[row][col].isEmpty) {
                std::cout << ".  ";        // Dot marks an empty square
            } else {
                std::cout << board[row][col].symbol << "  ";
            }
        }
        std::cout << "| " << (8 - row) << "\n";
    }

    std::cout << "   ------------------------\n";
    std::cout << "    a  b  c  d  e  f  g  h\n\n";
}

// Basic move validation applied to all pieces
bool ChessBoard::isValidMove(int fromRow, int fromCol, int toRow, int toCol, bool whiteTurn) const {
    Piece from = board[fromRow][fromCol];
    Piece to = board[toRow][toCol];

    if (from.isEmpty) return false;                          // Can't move an empty square
    if (from.isWhite != whiteTurn) return false;             // Can't move opponent's piece
    if (!to.isEmpty && to.isWhite == whiteTurn) return false;// Can't capture your own piece

    return true;
}

// Validate and execute a move, check for king capture
bool ChessBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol, bool whiteTurn) {
    if (!isValidMove(fromRow, fromCol, toRow, toCol, whiteTurn)) {
        std::cout << "Invalid move! Try again.\n";
        return false;
    }

    // Check for king capture before overwriting the square
    if (board[toRow][toCol].symbol == 'k' || board[toRow][toCol].symbol == 'K') {
        std::cout << "\n*** King captured! ";
        if (whiteTurn) {
            std::cout << "White wins! ***\n";
        } else {
            std::cout << "Black wins! ***\n";
        }
        wasCaptured = true;
    }

    // Move piece to new square and clear the old one
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = {' ', false, true};

    return true;
}

// Simple getter for the king capture flag
bool ChessBoard::kingCaptured() const {
    return wasCaptured;
}
