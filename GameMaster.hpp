#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include "GameLogic.hpp"
#include "BoardWidget.hpp"
#include "Selector.hpp"
#include <vector>
#include <string>

class GameMaster {
private:
    GameLogic* _logic;
    std::vector<Widget*> _widgets;
    BoardWidget* _board_widget;

    Selector* _mode_selector;
    std::string _last_mode;

public:
    GameMaster();
    ~GameMaster();
    void run();
};

#endif
