#ifndef POINT_H
#define POINT_H

#include <inc/gameobj/GameObj.h>
#include <inc/col/ColCircle.h>

#include <SFML/Graphics.hpp>

class Point : public GameObj{
    private:
        const int RADIUS;
        int value;

        sf::Sprite sprPoint;
        sf::Vector2f position;

        ColCircle* colCircle;

    public:
        Point();
        ~Point();

        void init(sf::Texture*, sf::Vector2f);
        void update(float delta);
        void render(sf::RenderWindow &window);

        ColCircle getColCircle(){ return *colCircle; }
};



#endif
