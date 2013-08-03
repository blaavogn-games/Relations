#ifndef COLCIRCLE_H
#define COLCIRCLE_H
#include <SFML/System.hpp>

class ColCircle{
private:
	float radius;
	sf::Vector2f position;

public:
	ColCircle(sf::Vector2f position, float radius = 0);

	float getRadius(){return radius;}
	void setRadius(float radius){this->radius = radius;}
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position){this->position = position;}


};
#endif
