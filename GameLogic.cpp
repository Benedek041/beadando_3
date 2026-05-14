#include "GameLogic.hpp"

GameLogic::GameLogic(int size, bool vs_ai, Player ai_player)
    : _size(size), _current_player(PLAYER_X), _winner(NONE), _moves_made(0), _vs_ai(vs_ai), _ai_player(ai_player) {
    _board.assign(size, std::vector<Player>(size, NONE));
}

bool GameLogic::make_move(int row, int col) {
    if (_winner != NONE || _board[row][col] != NONE) return false;

    _board[row][col] = _current_player;
    _moves_made++;

    check_win(row, col);

    if (_winner == NONE) {
        _current_player = (_current_player == PLAYER_X) ? PLAYER_O : PLAYER_X;
    }
    return true;
}

bool GameLogic::check_direction(int r, int c, int dr, int dc) const {
    Player p = _board[r][c];
    int count = 1;

    for (int i = 1; i < 5; ++i) {
        int nr = r + dr * i, nc = c + dc * i;
        if (nr < 0 || nr >= _size || nc < 0 || nc >= _size || _board[nr][nc] != p) break;
        count++;
    }
    for (int i = 1; i < 5; ++i) {
        int nr = r - dr * i, nc = c - dc * i;
        if (nr < 0 || nr >= _size || nc < 0 || nc >= _size || _board[nr][nc] != p) break;
        count++;
    }
    return count >= 5;
}

void GameLogic::check_win(int r, int c) {
    if (check_direction(r, c, 0, 1) || check_direction(r, c, 1, 0) ||
        check_direction(r, c, 1, 1) || check_direction(r, c, 1, -1)) {
        _winner = _board[r][c];
    }
}

    void GameLogic::reset(bool vs_ai) {
    _board.assign(_size, std::vector<Player>(_size, NONE));
    _current_player = PLAYER_X;
    _winner = NONE;
    _moves_made = 0;
    _vs_ai = vs_ai;
}

// ==========================================
// AI: MEZŐ ÉRTÉKELÉSE
// ==========================================
int GameLogic::evaluate_cell(int r, int c, Player p) const {
    int score = 0;
    int dr[] = {0, 1, 1, 1};
    int dc[] = {1, 0, 1, -1};

    for (int i = 0; i < 4; ++i) {
        int count = 1;
        int open_ends = 0;

        int f_r = r + dr[i], f_c = c + dc[i];
        while (f_r >= 0 && f_r < _size && f_c >= 0 && f_c < _size && _board[f_r][f_c] == p) {
            count++; f_r += dr[i]; f_c += dc[i];
        }
        if (f_r >= 0 && f_r < _size && f_c >= 0 && f_c < _size && _board[f_r][f_c] == NONE) open_ends++;

        int b_r = r - dr[i], b_c = c - dc[i];
        while (b_r >= 0 && b_r < _size && b_c >= 0 && b_c < _size && _board[b_r][b_c] == p) {
            count++; b_r -= dr[i]; b_c -= dc[i];
        }
        if (b_r >= 0 && b_r < _size && b_c >= 0 && b_c < _size && _board[b_r][b_c] == NONE) open_ends++;

        // Pontozás
        if (count >= 5) score += 100000;                     // Győzelem
        else if (count == 4 && open_ends > 0) score += 10000; // Majdnem győzelem (vagy vereség)
        else if (count == 3 && open_ends == 2) score += 5000; // Nyílt 3-as
        else if (count == 3 && open_ends == 1) score += 500;  // Zárt 3-as
        else if (count == 2 && open_ends == 2) score += 100;  // Nyílt 2-es
    }
    return score;
}

void GameLogic::make_ai_move() {
    int best_score = -1;
    int best_r = _size / 2;
    int best_c = _size / 2;

    Player opponent = (_ai_player == PLAYER_X) ? PLAYER_O : PLAYER_X;

    for (int r = 0; r < _size; ++r) {
        for (int c = 0; c < _size; ++c) {
            if (_board[r][c] == NONE) {
                // Támadás
                int attack_score = evaluate_cell(r, c, _ai_player);
                // Védekezés
                int defense_score = evaluate_cell(r, c, opponent);

                int total_score = attack_score + defense_score + (defense_score > 5000 ? defense_score : 0);

                if (total_score > best_score) {
                    best_score = total_score;
                    best_r = r;
                    best_c = c;
                }
            }
        }
    }

    if (_board[best_r][best_c] == NONE) {
        make_move(best_r, best_c);
    }

}
