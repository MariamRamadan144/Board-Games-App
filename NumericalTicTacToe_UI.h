#pragma once
#ifndef NUMERICAL_TICTACTOE_UI_H
#define NUMERICAL_TICTACTOE_UI_H

#include "BoardGame_Classes.h"
#include "NumericalTicTacToe_Board.h" // ���� ������ �� ���
#include <limits>

class NumericalTicTacToePlayer : public Player<int> {
public:
    NumericalTicTacToePlayer(const string& n, int sym, PlayerType t)
        : Player<int>(n, sym, t) {}
};

class NumericalTicTacToeUI : public UI<int> {
public:
    NumericalTicTacToeUI() : UI<int>("Welcome to Numerical Tic Tac Toe!", 3) {}

    // create player override (not used in main below but provided)
    Player<int>* create_player(string& name, int symbol, PlayerType type) override {
        return new NumericalTicTacToePlayer(name, symbol, type);
    }

    // get_move: ask for row col number, validate parity and usage
    Move<int>* get_move(Player<int>* player) override {
        int x, y, num;

        // determine allowed parity
        bool playerIsOdd = (player->get_symbol() % 2 != 0);

        // get board pointer to check used numbers
        Board<int>* bptr = player->get_board_ptr();
        NumericalTicTacToeBoard* nb = dynamic_cast<NumericalTicTacToeBoard*>(bptr);
        if (!nb) {
            cout << "Internal error: board pointer invalid.\n";
            return new Move<int>(0, 0, 0);
        }

        while (true) {
            cout << "\n" << player->get_name() << " (" << (playerIsOdd ? "Odd" : "Even")
                << ") - Enter your move as: row col number  (e.g. 0 0 5) : ";
            if (!(cin >> x >> y >> num)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Try again.\n";
                continue;
            }

            // validate coords
            if (x < 0 || x >= nb->get_rows() || y < 0 || y >= nb->get_columns()) {
                cout << "Invalid cell coordinates. Try again.\n";
                continue;
            }

            // validate number range
            if (num < 1 || num > 9) {
                cout << "Number must be between 1 and 9.\n";
                continue;
            }

            // validate parity
            if (playerIsOdd && (num % 2 == 0)) {
                cout << "You must choose an odd number.\n";
                continue;
            }
            if (!playerIsOdd && (num % 2 != 0)) {
                cout << "You must choose an even number.\n";
                continue;
            }

            // validate number not used
            if (nb->number_is_used(num)) {
                cout << "That number was already used. Pick another.\n";
                continue;
            }

            // validate cell empty
            auto mat = nb->get_board_matrix();
            if (mat[x][y] != 0) {
                cout << "Cell not empty. Choose another cell.\n";
                continue;
            }

            // all good
            break;
        }

        return new Move<int>(x, y, num);
    }
};

#endif // NUMERICAL_TICTACTOE_UI_H
