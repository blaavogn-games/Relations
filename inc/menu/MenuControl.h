#ifndef MENUCONTROL_H
#define MENUCONTROL_H

#include <SFML/Graphics.hpp>

#include <inc/gameobj/GameObj.h>
#include <inc/menu/Button.h>

#include <vector>

class ProgramControl;

//Welcome to the Power Point menu, all rights reserved Microsoft

class MenuControl : public GameObj{
    private:
        ProgramControl *programControl;

        sf::Sprite sprTitle, sprInfo;
        sf::Texture texTitle, texControls, texCredits;
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
