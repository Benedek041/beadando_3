#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP

#include <vector>

enum Player { NONE, PLAYER_X, PLAYER_O };

class GameLogic {
private:
    int _size;
    std::vector<std::vector<Player>> _board;
    Player _current_player;
    Player _winner;
    int _moves_made;

    // AI
    bool _vs_ai;
    Player _ai_player;

    bool check_direction(int r, int c, int dr, int dc) const;

    int evaluate_cell(int r, int c, Player p) const;

public:
    void reset(bool vs_ai);

    GameLogic(int size = 15, bool vs_ai = true, Player ai_player = PLAYER_O);

    bool make_move(int row, int col);
    void check_win(int r, int c);

    // AI
    void make_ai_move();

    Player get_cell(int r, int c) const { return _board[r][c]; }
    Player get_current_player() const { return _current_player; }
    Player get_winner() const { return _winner; }
    bool is_full() const { return _moves_made == _size * _size; }
    int get_size() const { return _size; }
    bool is_vs_ai() const { return _vs_ai; }
    Player get_ai_player() const { return _ai_player; }
};

#endif
