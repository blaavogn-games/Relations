#include "inc/col/ColRectangle.h"

#include <iostream>

ColRectangle::ColRectangle(sf::Vector2f position, float width, float height) : ColShape(position){
    //CLockwise
    addCorner(sf::Vector2f(0.0f,0.0f));
    addCorner(sf::Vector2f(width,0.0f));
    addCorner(sf::Vector2f(width,height));
    addCorner(sf::Vector2f(0.0f,height));
}

ColRectangle::~ColRectangle(){
    std::cout << "Alhoa" << std::endl;
}
