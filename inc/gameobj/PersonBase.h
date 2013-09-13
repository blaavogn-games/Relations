#ifndef PERSONBASE_H
#define PERSONBASE_H

#include <inc/col/ColShape.h>
#include <inc/gameobj/GameObj.h>

#include <SFML/Graphics.hpp>

class PersonBase : public GameObj{
    protected:
        const sf::Vector2f CENTER;
        sf::Vector2f position;
        ColShape* col;

        sf::Sprite sprPerson;
        sf::Texture* texPerson;

        float rotation, time, animationSpeed;

        void calculateSprite(float delta, sf::Vector2f* rotation, bool moving);

    public:
        PersonBase(sf::Vector2f, sf::Texture*);
        virtual ~PersonBase();
        virtual void init();
        virtual void render(sf::RenderWindow &window);

        void setPosition(sf::Vector2f);

        ColShape* getCol(){return col;}
        sf::Vector2f getPosition(){return position;}
        sf::Vector2i getCoordinate();

};


#endif
