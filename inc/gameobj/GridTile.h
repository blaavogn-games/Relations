#ifndef GRIDTILE_H
#define GRIDTILE_H
#include <SFML/Graphics.hpp>

#include <inc/gameobj/GameObj.h>
#include <inc/col/ColRectangle.h>

class GridTile : protected GameObj{
    private:
        sf::Sprite sprite;
        sf::Vector2f position;

        bool wall;
        ColShape* collision;

    public:

        GridTile();
        ~GridTile();

        void init(sf::Texture* texture, sf::Vector2f position);
        //Nothing happening on update
        void render(sf::RenderWindow &window);

        void setTexture(sf::Texture* texture);

        void setWall();
        bool isWall(){ return wall; }

        ColShape* getCollision(){return collision;}
};


#endif
