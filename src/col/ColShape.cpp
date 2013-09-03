#include "inc/col/ColShape.h"
#include "inc/col/Collision.h"
#include "inc/col/math/MathVector.h"
#include "inc/col/math/MathEssential.h"

#include <iostream>

ColShape::ColShape(sf::Vector2f position){
    absCornersCalculated = false;
    //sepAxesCalculated isn't used but will be if I decide to implement a roation function
    sepAxesCalculated = false;
    setPosition(position);
}

    ColShape::~ColShape(){
}

//Private
void ColShape::calculateAbsCorners(){
    absCorners.clear();
    for(std::vector<sf::Vector2f>::iterator it = relCorners.begin(); it != relCorners.end(); ++it){
        absCorners.push_back(sf::Vector2f(position.x + it->x,position.y + it->y));
    }
    absCornersCalculated = true;
}

void ColShape::calculateSepAxes(){
    sepAxes.clear();
    sf::Vector2f tempCorner = relCorners.back();
    for(std::vector<sf::Vector2f>::iterator it = relCorners.begin(); it != relCorners.end(); ++it){
        float xEdge = it->x - tempCorner.x;
        float yEdge = it->y - tempCorner.y;

        //Finds a vector orthogonal to the edge (-y , x) is orthogonal to (x,y)
        sf::Vector2f tempSepAxis(-yEdge, xEdge);


        //To get only unique seperating axes all axes are normalized and their direction is changed to have a positive x value.
        //(Or positive y-value if x = 0)
        //The nomalization is also assumed by the Collision class when corners are projected
        tempSepAxis = MathVector::normalize(tempSepAxis);

        if((tempSepAxis.x < 0) || (tempSepAxis.x == 0 && tempSepAxis.y < 0)) {
            tempSepAxis.x *= -1;
            tempSepAxis.y *= -1;
        }


        if(Collision::doesAxisExist(tempSepAxis, &sepAxes) == false){
            sepAxes.push_back(tempSepAxis);
        }

        tempCorner = *it;
    }
}



//Public


void ColShape::setPosition(sf::Vector2f position){
    this->position = position;
    absCornersCalculated = false;
}

void ColShape::move(sf::Vector2f movement){
    position += movement;
    absCornersCalculated = false;
}

void ColShape::addCorner(sf::Vector2f position){
    relCorners.push_back(position);
    absCornersCalculated = false;
}

std::vector<sf::Vector2f>* ColShape::getCorners(){
    if(!absCornersCalculated){
        calculateAbsCorners();
        absCornersCalculated = true;
    }

    return &absCorners;
}

int ColShape::getCorner(int baseCorner, int relation){

    signed int relCorner = baseCorner + relation;

    if(relCorner < 0){
        relCorner += absCorners.size();
    }
    else if(relCorner >= (signed int) absCorners.size()){
        relCorner -= absCorners.size();
    }

    return relCorner;

}

std::vector<sf::Vector2f> ColShape::getSepAxes(){
    if(!sepAxesCalculated){
        calculateSepAxes();
        sepAxesCalculated = true;
    }

    return sepAxes;
}
