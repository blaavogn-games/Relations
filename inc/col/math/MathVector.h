#ifndef MATHVECTOR_H
#define MATHVECTOR_H
#include <SFML/System.hpp>
#include <cmath>

class MathVector{

public:
	static float distance(sf::Vector2f v1,sf::Vector2f v2);
	static sf::Vector2f normalize(sf::Vector2f);
    static sf::Vector2f project(sf::Vector2f, sf::Vector2f, sf::Vector2f offset = sf::Vector2f(0,0));
    static sf::Vector2f scale(sf::Vector2f, float);
};
#endif
