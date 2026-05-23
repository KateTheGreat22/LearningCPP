#include "chess.h"

int main() {
    ChessBoard board;
    bool whiteTurn = true;
    bool gameOver = false;
    std::string input;

    std::cout << "Welcome to Terminal Chess!\n";
    std::cout << "Enter moves in format: e2 e4 (column then row)\n";
    std::cout << "Type 'quit' to exit the game\n";

    while (!gameOver) {
        board.display();

        // Prompt the current player
        if (whiteTurn) {
            std::cout << "White's turn: ";
        } else {
            std::cout << "Black's turn: ";
        }

        std::getline(std::cin, input);

        if (input == "quit") {
            std::cout << "Thanks for playing!\n";
            break;
        }

        // Input must be exactly 5 characters (e.g. "e2 e4")
        if (input.length() != 5) {
            std::cout << "Invalid format! Use format: e2 e4\n";
            continue;
        }

        // Convert letter/number input into row and column indices
        int fromCol = input[0] - 'a';
        int fromRow = 8 - (input[1] - '0');
        int toCol = input[3] - 'a';
        int toRow = 8 - (input[4] - '0');

        // Reject anything outside the 8x8 grid
        if (fromCol < 0 || fromCol > 7 || fromRow < 0 || fromRow > 7 ||
            toCol < 0 || toCol > 7 || toRow < 0 || toRow > 7) {
            std::cout << "Coordinates out of bounds! Try again.\n";
            continue;
        }

        if (board.movePiece(fromRow, fromCol, toRow, toCol, whiteTurn)) {
            // End the game if a king was captured, otherwise switch turns
            if (board.kingCaptured()) {
                gameOver = true;
            } else {
                whiteTurn = !whiteTurn;
            }
        }
    }

    std::cout << "Game over! Thanks for playing.\n";
    return 0;
}
