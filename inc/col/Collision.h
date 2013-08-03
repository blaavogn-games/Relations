#ifndef COLLISION_H
#define COLLISION_H
#include <SFML/System.hpp>
#include "ColCircle.h"
#include "ColShape.h"

class Collision{
private:
    static bool inBetween(sf::Vector2f, sf::Vector2f);
    static sf::Vector2f movePFromP(sf::Vector2f, sf::Vector2f, float);

public:
	static bool doesCollide(ColCircle, ColCircle);
    static bool doesCollide(ColCircle*, ColShape*, sf::Vector2f*);

};
#endif
