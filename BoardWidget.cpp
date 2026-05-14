#include "BoardWidget.hpp"

using namespace genv;

BoardWidget::BoardWidget(int x, int y, int cell_size, GameLogic* logic)
    : Widget(x, y, logic->get_size() * cell_size, logic->get_size() * cell_size),
      _logic(logic), _cell_size(cell_size), _has_click(false) {}

void BoardWidget::draw() const {
    int s = _logic->get_size();

    for (int r = 0; r < s; ++r) {
        for (int c = 0; c < s; ++c) {
            int cx = _x + c * _cell_size;
            int cy = _y + r * _cell_size;

            // Cella háttere és kerete
            gout << move_to(cx, cy) << color(200, 200, 200) << box(_cell_size, _cell_size);
            gout << move_to(cx+1, cy+1) << color(255, 255, 255) << box(_cell_size-2, _cell_size-2);

            // X vagy O kirajzolása
            Player p = _logic->get_cell(r, c);
            if (p == PLAYER_X) {
                gout << color(255, 0, 0); // Piros X
                gout << move_to(cx+5, cy+5) << line(_cell_size-10, _cell_size-10);
                gout << move_to(cx+_cell_size-5, cy+5) << line(-_cell_size+10, _cell_size-10);
            } else if (p == PLAYER_O) {
                // O kirajzolása, ami inkább négyzet
                gout << color(0, 0, 255);
                gout << move_to(cx+5, cy+5) << box(_cell_size-10, _cell_size-10);
                gout << move_to(cx+8, cy+8) << color(255,255,255) << box(_cell_size-16, _cell_size-16);
            }
        }
    }
}

void BoardWidget::handle_event(const event& ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        if (is_selected(ev.pos_x, ev.pos_y)) {
            _last_clicked_col = (ev.pos_x - _x) / _cell_size;
            _last_clicked_row = (ev.pos_y - _y) / _cell_size;
            _has_click = true;
        }
    }
}
