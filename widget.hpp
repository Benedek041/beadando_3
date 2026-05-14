#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"

class Widget {
protected:
    int _x, _y, _size_x, _size_y;
    bool _is_focused;

public:
    Widget(int x, int y, int sx, int sy) : _x(x), _y(y), _size_x(sx), _size_y(sy), _is_focused(false) {}
    virtual ~Widget() {}

    virtual void draw() const = 0;
    virtual void handle_event(const genv::event& ev) = 0;

    virtual bool is_selected(int mouse_x, int mouse_y) const {
        return mouse_x >= _x && mouse_x <= _x + _size_x && mouse_y >= _y && mouse_y <= _y + _size_y;
    }

    virtual void set_focus(bool focus) { _is_focused = focus; }
    bool get_focus() const { return _is_focused; }
};

#endif // WIDGET_HPP
