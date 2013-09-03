#ifndef COLLISION_H
#define COLLISION_H
#include <SFML/System.hpp>

#include "inc/col/ColCircle.h"
#include "inc/col/ColShape.h"
#include "inc/col/math/MathVector.h"
#include "inc/col/math/MathEssential.h"

#include <iostream>
#include <vector>
#include <cfloat>


class Collision{
private:
    static bool inBetween(sf::Vector2f, sf::Vector2f);
    static sf::Vector2f movePFromP(sf::Vector2f, sf::Vector2f, float);
    static std::vector<sf::Vector2f> getOuterProjection(sf::Vector2f, std::vector<sf::Vector2f>*, bool);

public:
	static bool doesCollide(ColCircle, ColCircle);
    static bool doesCollide(ColCircle*, ColShape*, sf::Vector2f*);
    static bool doesCollide(ColShape*, ColShape*, sf::Vector2f*);

    static bool doesAxisExist(sf::Vector2f, std::vector<sf::Vector2f>*);
};
#endif
