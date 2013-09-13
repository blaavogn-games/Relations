#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

#include <inc/gameobj/GameObj.h>

class MenuControl;

class Button : public GameObj{
    private:
        MenuControl* menuControl;
        sf::Sprite sprite;
        sf::Texture texture;

        bool hover, firstMousePress;
        int type, width;

    public:
        Button(MenuControl*);
        ~Button();

        void init(int, sf::Vector2f);
        void update(sf::Vector2i &mousePosition);
        void render(sf::RenderWindow &window);


};


#endif
