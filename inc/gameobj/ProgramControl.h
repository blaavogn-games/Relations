#ifndef PROGRAMCONTROL_H
#define PROGRAMCONTROL_H

#include <SFML/Graphics.hpp>

#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/GameControl.h>
#include <inc/menu/MenuControl.h>


class ProgramControl : public GameObj{
    private:
        GameControl *gameControl;
        MenuControl *menuControl;

        bool closeWindow;

        enum ProgramState{
            MENU_STATE,
            GAME_STATE
        };

        ProgramState state;

    public:
        ProgramControl();
        ~ProgramControl();

        void init();
        void update(float, sf::Vector2i);
        void render(sf::RenderWindow &window);
        void close();
        void startGame();
        void enterMenuState();
};

#endif
