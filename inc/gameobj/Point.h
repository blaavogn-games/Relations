#ifndef POINT_H
#define POINT_H

#include <inc/gameobj/GameObj.h>
#include <inc/col/ColCircle.h>

#include <SFML/Graphics.hpp>

class Point : public GameObj{
    private:
        const int RADIUS, GRIDOFFSET;
        float value;

        sf::Sprite sprPoint;
        sf::Vector2i coordinate;
        sf::Vector2f position;

        ColCircle* colCircle;

    public:
        Point();
        ~Point();

        void init(sf::Texture*, sf::Vector2i);
        void update(float delta);
        void render(sf::RenderWindow &window);

        float getValue();

        sf::Vector2i getCoordinate(){ return coordinate; }
        ColCircle* getColCircle(){ return colCircle; }
};



#endif
