#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include "Widget.hpp"
#include <vector>
#include <string>

class Selector : public Widget {
private:
    std::vector<std::string> _items;
    int _selected_index;
    int _scroll_offset;
    int _visible_items;
    int _item_height;
    bool _is_open;

public:
    Selector(int x, int y, int sx, int item_h, int visible_count, const std::vector<std::string>& items);

    void draw() const override;
    void handle_event(const genv::event& ev) override;

    bool is_selected(int mouse_x, int mouse_y) const override;

    std::string get_value() const;
};

#endif // SELECTOR_HPP
