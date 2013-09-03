#include "inc/col/ColRectangle.h"

#include <iostream>

ColRectangle::ColRectangle(sf::Vector2f position, float width, float height) : ColShape(position, sf::Vector2f(width/2, height/2)){
    //CLockwise
    addCorner(sf::Vector2f(0.0f,0.0f));
    addCorner(sf::Vector2f(width,0.0f));
    addCorner(sf::Vector2f(width,height));
    addCorner(sf::Vector2f(0.0f,height));
    init();
}

ColRectangle::~ColRectangle(){
}
