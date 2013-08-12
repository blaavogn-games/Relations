#include "inc/col/math/MathVector.h"
#include <cassert>
#include <iostream>

float MathVector::distance(sf::Vector2f v1, sf::Vector2f v2){
	//Finds the difference in x and y
	float deltaX = v1.x - v2.x , deltaY = v1.y - v2.y;

	//Pythagoras c^2 = a^2 + b^2
	return sqrt(powf(deltaX,2) + powf(deltaY,2));
}

sf::Vector2f MathVector::normalize(sf::Vector2f vector){
    float length = sqrt(powf(vector.x,2) + powf(vector.y,2));
    //Assuming an actual vector is given
    assert(length != 0);
    return sf::Vector2f(vector.x / length , vector.y / length);

}

sf::Vector2f MathVector::scale(sf::Vector2f vector, float scale){
    return sf::Vector2f(vector.x * scale , vector.y * scale);

}


sf::Vector2f MathVector::project(sf::Vector2f point, sf::Vector2f vector, sf::Vector2f offset){
    //Projects point onto vector

    sf::Vector2f proj;
    sf::Vector2f projPoint(point.x - offset.x, point.y - offset.y);

    float dp = projPoint.x * vector.x + projPoint.y * vector.y;
    float vectorLengthP = (vector.x*vector.x + vector.y*vector.y);

    proj.x = ( dp / vectorLengthP ) * vector.x;
    proj.y = ( dp / vectorLengthP ) * vector.y;

    return proj;
}
