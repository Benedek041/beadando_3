#include "GameMaster.hpp"
#include "graphics.hpp"
#include <iostream>

using namespace genv;

const int XX = 15 * 40;
const int YY = 15 * 40 + 150;

GameMaster::GameMaster() {
    _logic = new GameLogic(15, true, PLAYER_O);

    gout.open(XX, YY);

    std::vector<std::string> modes = {"1 Jatekos (Gep ellen)", "2 Jatekos (Egymas ellen)"};
    _mode_selector = new Selector(10, 10, 250, 30, 2, modes);
    _widgets.push_back(_mode_selector);
    _last_mode = modes[0];

    _board_widget = new BoardWidget(0, 100, 40, _logic);
    _widgets.push_back(_board_widget);
}

GameMaster::~GameMaster() {
    delete _logic;
    for (Widget* w : _widgets) delete w;
}

void GameMaster::run() {
    event ev;
    Widget* focus = nullptr;

    while (gin >> ev && ev.keycode != key_escape) {

        if (ev.type == ev_mouse && ev.button == btn_left) {
            for (Widget* w : _widgets) {
                if (w->is_selected(ev.pos_x, ev.pos_y)) {
                    if (focus) focus->set_focus(false);
                    focus = w;
                    focus->set_focus(true);
                }
            }
        }

        if (focus) focus->handle_event(ev);
        _board_widget->handle_event(ev);

        std::string current_mode = _mode_selector->get_value();
        bool mode_changed = (current_mode != _last_mode);
        bool restart_pressed = (ev.type == ev_key && (ev.keycode == 'r' || ev.keycode == 'R'));

        if (mode_changed || restart_pressed) {
            _last_mode = current_mode;
            bool vs_ai = (current_mode == "1 Jatekos (Gep ellen)");
            _logic->reset(vs_ai);
        }

        if (_board_widget->has_pending_click()) {
            int r, c;
            _board_widget->get_click(r, c);

            if (_logic->get_winner() == NONE && !_logic->is_full()) {
                if (_logic->make_move(r, c)) {
                    if (_logic->is_vs_ai() && _logic->get_current_player() == _logic->get_ai_player()
                        && _logic->get_winner() == NONE && !_logic->is_full()) {
                        _logic->make_ai_move();
                    }
                }
            }
        }

        gout << move_to(0, 0) << color(50, 50, 50) << box(XX, YY);

        _board_widget->draw();
        _mode_selector->draw();

        gout << move_to(10, 15 * 40 + 130) << color(255, 255, 255);
        if (_logic->get_winner() == PLAYER_X) gout << text("Gyoztes: X!");
        else if (_logic->get_winner() == PLAYER_O) gout << text("Gyoztes: O!");
        else if (_logic->is_full()) gout << text("A jatek dontetlen!");
        else {
            if (_logic->get_current_player() == PLAYER_X) gout << text("X kovetkezik");
            else gout << text("O kovetkezik");
        }

        gout << move_to(XX - 200, 15 * 40 + 130) << color(150, 150, 150);
        gout << text("Uj jatek: 'R' gomb");

        gout << refresh;
    }
}
