#ifndef WALL_H
#define WALL_H
#include "inc/gameobj/GameObj.h"
#include <SFML/Graphics.hpp>
#include "inc/col/ColRectangle.h"

class Wall : protected GameObj{
    private:
        sf::Texture texture;
        ColRectangle* colRectangle;
        sf::Vector2f position;
        sf::Sprite sprite;

    public:
        Wall(sf::Vector2f);
        ~Wall();
        void init();
        void update(sf::Vector2i &mousePosition, float delta);
        void render(sf::RenderWindow &window);
        ColRectangle* getCol();
};

#endif
