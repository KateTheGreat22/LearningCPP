#include "chess.h"

// Constructor: calls initBoard to set up all pieces
ChessBoard::ChessBoard() {
    wasCaptured = false;
    initBoard();
}

// Places all pieces in their starting positions
void ChessBoard::initBoard() {
    char backRow[8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};

    for (int col = 0; col < 8; col++) {
        board[0][col] = {(char)tolower(backRow[col]), false, false};
        board[1][col] = {'p', false, false};

        for (int row = 2; row <= 5; row++) {
            board[row][col] = {' ', false, true};
        }

        board[6][col] = {'P', true, false};
        board[7][col] = {backRow[col], true, false};
    }
}

// Displays the current board state in the terminal
void ChessBoard::display() const {
    std::cout << "\n    a  b  c  d  e  f  g  h\n";
    std::cout << "   ------------------------\n";

    for (int row = 0; row < 8; row++) {
        std::cout << (8 - row) << " | ";

        for (int col = 0; col < 8; col++) {
            if (board[row][col].isEmpty) {
                std::cout << ".  ";
            } else {
                std::cout << board[row][col].symbol << "  ";
            }
        }
        std::cout << "| " << (8 - row) << "\n";
    }

    std::cout << "   ------------------------\n";
    std::cout << "    a  b  c  d  e  f  g  h\n\n";
}

// Checks if a move is valid for the current player
bool ChessBoard::isValidMove(int fromRow, int fromCol, int toRow, int toCol, bool whiteTurn) const {
    Piece from = board[fromRow][fromCol];
    Piece to = board[toRow][toCol];

    if (from.isEmpty) return false;
    if (from.isWhite != whiteTurn) return false;
    if (!to.isEmpty && to.isWhite == whiteTurn) return false;

    return true;
}

// Executes a move on the board after validating it
bool ChessBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol, bool whiteTurn) {
    if (!isValidMove(fromRow, fromCol, toRow, toCol, whiteTurn)) {
        std::cout << "Invalid move! Try again.\n";
        return false;
    }

    // Check if a king is being captured
    if (board[toRow][toCol].symbol == 'k' || board[toRow][toCol].symbol == 'K') {
        std::cout << "\n*** King captured! ";
        if (whiteTurn) {
            std::cout << "White wins! ***\n";
        } else {
            std::cout << "Black wins! ***\n";
        }
        wasCaptured = true;
    }

    // Move the piece and clear the old square
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = {' ', false, true};

    return true;
}

// Returns true if a king was captured
bool ChessBoard::kingCaptured() const {
    return wasCaptured;
}
