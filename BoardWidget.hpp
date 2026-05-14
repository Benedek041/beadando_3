#ifndef BOARDWIDGET_HPP
#define BOARDWIDGET_HPP

#include "Widget.hpp"
#include "GameLogic.hpp"

class BoardWidget : public Widget {
private:
    GameLogic* _logic;
    int _cell_size;

    int _last_clicked_row;
    int _last_clicked_col;
    bool _has_click;

public:
    BoardWidget(int x, int y, int cell_size, GameLogic* logic);

    void draw() const override;
    void handle_event(const genv::event& ev) override;

    bool has_pending_click() const { return _has_click; }
    void get_click(int& r, int& c) { r = _last_clicked_row; c = _last_clicked_col; _has_click = false; }
};

#endif
