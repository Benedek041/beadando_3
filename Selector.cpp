#include "Selector.hpp"
#include <algorithm>

using namespace genv;

Selector::Selector(int x, int y, int sx, int item_h, int visible_count, const std::vector<std::string>& items)
    : Widget(x, y, sx, item_h), _items(items), _visible_items(visible_count), _item_height(item_h) {
    _selected_index = 0;
    _scroll_offset = 0;
    _is_open = false;
}

bool Selector::is_selected(int mouse_x, int mouse_y) const {
    int current_height = _is_open ? _item_height * (_visible_items + 1) : _item_height;
    return mouse_x >= _x && mouse_x <= _x + _size_x && mouse_y >= _y && mouse_y <= _y + current_height;
}

void Selector::draw() const {
    gout << move_to(_x, _y) << color(200, 200, 200) << box(_size_x, _item_height);

    gout << move_to(_x + 5, _y + _item_height - 5) << color(0, 0, 0);
    if (!_items.empty()) {
        gout << text(_items[_selected_index]);
    }

    // Lefelé mutató háromszög
    int tri_x = _x + _size_x - 20;
    int tri_y = _y + _item_height / 2 - 2;
    gout << color(50, 50, 50);
    for(int i = 0; i < 5; i++) {
        gout << move_to(tri_x + i, tri_y + i) << line(10 - 2 * i, 0);
    }

    if (_is_open) {
        int list_y = _y + _item_height;
        gout << move_to(_x, list_y) << color(150, 150, 150) << box(_size_x, _item_height * _visible_items);

        for (int i = 0; i < _visible_items; ++i) {
            int actual_index = _scroll_offset + i;
            if (actual_index < _items.size()) {
                // Kijelölt elem más háttérszínnel
                if (actual_index == _selected_index) {
                    gout << move_to(_x, list_y + i * _item_height) << color(100, 100, 250) << box(_size_x, _item_height);
                }
                gout << move_to(_x + 5, list_y + i * _item_height + _item_height - 5) << color(0, 0, 0) << text(_items[actual_index]);
            }
        }
    }
}

void Selector::handle_event(const event& ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {

        if (ev.pos_x >= _x && ev.pos_x <= _x + _size_x &&
            ev.pos_y >= _y && ev.pos_y <= _y + _item_height) {
            _is_open = !_is_open;
        }
        else if (_is_open && ev.pos_x >= _x && ev.pos_x <= _x + _size_x &&
                 ev.pos_y > _y + _item_height && ev.pos_y <= _y + _item_height * (_visible_items + 1)) {

            int clicked_relative_y = ev.pos_y - (_y + _item_height);
            int clicked_index = _scroll_offset + (clicked_relative_y / _item_height);

            if (clicked_index < _items.size()) {
                _selected_index = clicked_index;
                _is_open = false;
            }
        }
        else if (_is_open) {
            _is_open = false;
        }
    }

}

std::string Selector::get_value() const {
    if (_items.empty()) return "";
    return _items[_selected_index];
}
