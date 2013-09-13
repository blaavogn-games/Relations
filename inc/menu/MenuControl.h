#ifndef MENUCONTROL_H
#define MENUCONTROL_H

#include <SFML/Graphics.hpp>

#include <inc/gameobj/GameObj.h>
#include <inc/menu/Button.h>

#include <vector>

class ProgramControl;

class MenuControl : public GameObj{
    private:
        ProgramControl *programControl;

        sf::Sprite sprTitle;
        sf::Texture texTitle;
        std::vector<Button*> buttons;

        enum MenuState{
            MAIN_MENU,
            CREDITS_MENU
        };

        MenuState state;

    public:
        MenuControl(ProgramControl *programControl);
        ~MenuControl();

        void init();
        void update(float, sf::Vector2i &mousePosition);
        void render(sf::RenderWindow &window);

        void action(int);
};

#endif
