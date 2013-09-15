#include "inc/col/ColShape.h"
#include "inc/col/Collision.h"
#include "inc/col/math/MathVector.h"
#include "inc/col/math/MathEssential.h"

#include <iostream>

ColShape::ColShape(sf::Vector2f position, sf::Vector2f center){
    this->position = position;
    this->center = center;
    rotation = 0;
}

ColShape::~ColShape(){}

void ColShape::init(){

    rotCorners = relCorners;

    calculateSepAxes();
    calculateAbsCorners();
}


//Private
void ColShape::calculateAbsCorners(){
    absCorners.clear();

    for(std::vector<sf::Vector2f>::iterator it = rotCorners.begin(); it != rotCorners.end(); ++it){
        absCorners.push_back(sf::Vector2f(position.x + it->x,position.y + it->y));
    }

}

void ColShape::calculateSepAxes(){
    sepAxes.clear();
    sf::Vector2f tempCorner = rotCorners.back();
    for(std::vector<sf::Vector2f>::iterator it = rotCorners.begin(); it != rotCorners.end(); ++it){
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



void ColShape::setRotation(float degree){
    rotation = degree;
    float radians = MathEssential::toRadians(degree);

    for(unsigned int i = 0; i < relCorners.size(); i++){
        sf::Vector2f delta = relCorners.at(i) - center;

        rotCorners.at(i).x = delta.x * cos(radians) - delta.y * sin(radians) + center.x;
        rotCorners.at(i).y = delta.x * sin(radians) + delta.y * cos(radians) + center.y;
    }

    calculateSepAxes();
    calculateAbsCorners();
}

void ColShape::setPosition(sf::Vector2f position){
    this->position = position;
    calculateAbsCorners();
}
void ColShape::move(sf::Vector2f movement){
    position += movement;
    calculateAbsCorners();
}

void ColShape::addCorner(sf::Vector2f position){
    relCorners.push_back(position);
}



int ColShape::getCorner(int baseCorner, int relation){

    signed int relCorner = baseCorner + relation; //SHITTY NAMING, this is NOT relCornerssssssssss

    if(relCorner < 0){
        relCorner += absCorners.size();
    }
    else if(relCorner >= (signed int) absCorners.size()){
        relCorner -= absCorners.size();
    }

    return relCorner;
}

std::vector<sf::Vector2f>* ColShape::getCorners(){
    return &absCorners;
}

std::vector<sf::Vector2f> ColShape::getSepAxes(){
    return sepAxes; //I am so inconsitent with using pointers
}
