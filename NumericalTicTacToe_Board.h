#pragma once
#ifndef NUMERICAL_TICTACTOE_BOARD_H
#define NUMERICAL_TICTACTOE_BOARD_H

#include "BoardGame_Classes.h"  // path ���� ���� ���� - ���� �� ����
#include <set>

class NumericalTicTacToeBoard : public Board<int> {
    std::set<int> usedNumbers;
public:
    NumericalTicTacToeBoard() : Board<int>(3, 3) {
        // Initialize board cells to 0 meaning empty
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i][j] = 0;
        n_moves = 0;
    }

    // Return true if move applied successfully
    bool update_board(Move<int>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        int num = move->get_symbol();

        // bounds
        if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
        // cell must be empty
        if (board[x][y] != 0) return false;
        // number must be in 1..9
        if (num < 1 || num > 9) return false;
        // number not used before
        if (usedNumbers.count(num) > 0) return false;

        board[x][y] = num;
        usedNumbers.insert(num);
        ++n_moves;
        return true;
    }

    // A player wins if any three numbers in a line sum to 15,
    // regardless of parity ownership (the last mover who completes 15 wins).
    bool is_win(Player<int>* player) override {
        auto line_is_player_and_sum15 = [&](int a, int b, int c) -> bool {
            int va = board[a / 3][a % 3];
            int vb = board[b / 3][b % 3];
            int vc = board[c / 3][c % 3];
            if (va == 0 || vb == 0 || vc == 0) return false; // empty cell exists
            return (va + vb + vc) == 15;
            };

        // rows
        if (line_is_player_and_sum15(0, 1, 2)) return true;
        if (line_is_player_and_sum15(3, 4, 5)) return true;
        if (line_is_player_and_sum15(6, 7, 8)) return true;
        // cols
        if (line_is_player_and_sum15(0, 3, 6)) return true;
        if (line_is_player_and_sum15(1, 4, 7)) return true;
        if (line_is_player_and_sum15(2, 5, 8)) return true;
        // diags
        if (line_is_player_and_sum15(0, 4, 8)) return true;
        if (line_is_player_and_sum15(2, 4, 6)) return true;

        return false;
    }

    bool is_lose(Player<int>* player) override {
        // Not used in our GameManager logic � keep false
        return false;
    }

    bool is_draw(Player<int>* player) override {
        // draw when board full and no one has a winning line
        if (n_moves < rows * columns) return false;
        // check both players: odd and even
        // create two dummy players with parity to test
        class DummyPlayer : public Player<int> {
        public:
            DummyPlayer(int s) : Player<int>("", s, PlayerType::HUMAN) {}
        };
        DummyPlayer oddP(1), evenP(2);
        oddP.set_board_ptr(this);
        evenP.set_board_ptr(this);

        // if either wins it's not draw
        if (is_win(&oddP) || is_win(&evenP)) return false;
        return true;
    }

    bool game_is_over(Player<int>* player) override {
        // end when current player wins OR board full (draw)
        // Note: we keep semantics consistent: if either parity-player has winning line, game over.
        // But here we check both parities to be safe.
        class DummyPlayer : public Player<int> {
        public:
            DummyPlayer(int s) : Player<int>("", s, PlayerType::HUMAN) {}
        };
        DummyPlayer oddP(1), evenP(2);
        oddP.set_board_ptr(this);
        evenP.set_board_ptr(this);

        return is_win(&oddP) || is_win(&evenP) || (n_moves == rows * columns);
    }

    // helper: check if a number already used (UI will call this)
    bool number_is_used(int num) const {
        return usedNumbers.count(num) > 0;
    }

    // expose board matrix getter (already available via base get_board_matrix)
};

#endif // NUMERICAL_TICTACTOE_BOARD_H
