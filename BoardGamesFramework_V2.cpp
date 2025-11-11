#include "BoardGame_Classes.h"
#include "NumericalTicTacToe_Board.h"
#include "NumericalTicTacToe_UI.h"
#include <limits>

int main() {
    while (true) {
        cout << "                          ====================================\n";
        cout << "                        Get Ready to Play — Let the Games Begin!\n";
        cout << "                          ====================================\n";
        cout << "Select a game to play:\n";
        cout << "1. SUS\n";
        cout << "2. Four-in-a-row\n";
        cout << "3. 5x5 Tic Tac Toe\n";
        cout << "4. Word Tic Tac Toe\n";
        cout << "5. Misère Tic Tac Toe\n";
        cout << "6. Diamond Tic Tac Toe\n";
        cout << "7. 4x4 Tic Tac Toe\n";
        cout << "8. Pyramid Tic Tac Toe\n";
        cout << "9. Numerical Tic Tac Toe (( Think before you play! ))\n";
        cout << "10. Obstacles Tic Tac Toe\n";
        cout << "11. Infinity Tic Tac Toe\n";
        cout << "12. Exit\n\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 12.\n\n";
            continue;
        }

        cout << "------------------------------------\n";

        if (choice == 12) {
            cout << "Goodbye!\n";
            break;
        }

        if (choice != 9) {
            cout << "This game mode is not available yet. Please choose option 9 or 12.\n\n";
            continue;
        }

        NumericalTicTacToeBoard board;
        NumericalTicTacToeUI ui;

        // create players: odd for Player 1, even for Player 2
        NumericalTicTacToePlayer p1("Player 1", 1, PlayerType::HUMAN);
        NumericalTicTacToePlayer p2("Player 2", 2, PlayerType::HUMAN);

        Player<int>* players[2] = { &p1, &p2 };
        GameManager<int> game(&board, players, &ui);
        game.run();

        cout << "------------------------------------\n\n";
    }
}
