#include "inc/col/Collision.h"
#include "inc/col/math/MathVector.h"
#include <iostream>
#include <vector>

bool Collision::doesCollide(ColCircle c1, ColCircle c2){
	sf::Vector2f pos1 = c1.getPosition();
	sf::Vector2f pos2 = c2.getPosition();

	if(MathVector::distance(pos1,pos2) > (c1.getRadius() + c2.getRadius())){
		return false;
	}
	return true;
}

bool Collision::doesCollide(ColCircle* circle, ColShape* shape, sf::Vector2f* returnVector){
	//ReturnVector is the vector that would move Circle out of shape

	/*	1. Find nearest corner to circle center
        1a. Compare radius to closestCorner dist
		2. Find the adjacent edges
		3. Project circle onto edges
		4. Checks which edges the projection is within (There must be 1 since radius < distance to corner)
		4a. Check the distance of to the projection on those edges
		*/

    //1
    sf::Vector2f circleCenter = circle->getPosition();
    float radius = circle->getRadius();
    std::vector<sf::Vector2f> corners = shape->getCorners();
    float cornerSum = corners.size();

    int closestCornerNum = 0;
    float closestDistance = MathVector::distance(circleCenter, corners.at(0));

    for(int i = 1; i < cornerSum; i++){
        float distance = MathVector::distance(circleCenter, corners.at(i));

        if(distance < closestDistance ){
            closestCornerNum = i;
            closestDistance = distance;
        }
    }



    //2
    sf::Vector2f closestCorner = corners.at(closestCornerNum);
    sf::Vector2f prevCorner = corners.at(shape->getCorner(closestCornerNum,-1));
    sf::Vector2f nextCorner = corners.at(shape->getCorner(closestCornerNum,1));

    sf::Vector2f prevEdge = closestCorner - prevCorner;
    sf::Vector2f nextEdge = closestCorner - nextCorner;

	//3
	sf::Vector2f prevProj = MathVector::project(circleCenter, prevEdge, prevCorner);
	sf::Vector2f nextProj = MathVector::project(circleCenter, nextEdge, nextCorner);

    //4
    bool prevWithin = Collision::inBetween(prevEdge, prevProj);
    bool nextWithin = Collision::inBetween(nextEdge, nextProj);

    //4a
    if(!prevWithin && !nextWithin){
        if ( radius > closestDistance ){
            *returnVector = Collision::movePFromP(circleCenter , corners.at(closestCornerNum), circle->getRadius());
            return true;
        }
    }else{
        //4b
        if (prevWithin){
            sf::Vector2f adjustedCenter(circleCenter.x - prevCorner.x, circleCenter.y  - prevCorner.y);
            if (radius > MathVector::distance(prevProj, adjustedCenter)) {
                prevProj += prevCorner;
                *returnVector = Collision::movePFromP(circleCenter , prevProj, circle->getRadius());
                return true;
            }
        }
        if (nextWithin){
            sf::Vector2f adjustedCenter(circleCenter.x - nextCorner.x, circleCenter.y  - nextCorner.y);

            if (radius > MathVector::distance(nextProj, adjustedCenter)) {
                nextProj += nextCorner;
                *returnVector = Collision::movePFromP(circleCenter , nextProj, circle->getRadius());
                return true;
            }
        }
    }
    return false;
}

bool Collision::inBetween(sf::Vector2f vector, sf::Vector2f point) {
    if (vector.x > .5 || vector.x < -.5){
        if ((point.x > 0 && point.x < vector.x)|| (point.x < 0 && point.x > vector.x)) {
            return true;
        }
    }
    else {
        if ((point.y > 0 && point.y < vector.y) || (point.y < 0 && point.y > vector.y)) {
            return true;
        }
    }

	return false;
}

sf::Vector2f Collision::movePFromP(sf::Vector2f moveP, sf::Vector2f fromP, float radius){
    sf::Vector2f deltaVector = fromP - moveP;

    float distance = MathVector::distance(moveP,fromP);
    float moveLength = radius - distance;
    float scale = moveLength / distance;

    //The magicNumber makes the code go never ending collisons in collision handling to 1 loop
    //I guess it is because the scale just moves the circle to the outermost collision point
    const float magicNumber = 1.01;
    deltaVector.x *= scale * magicNumber;
    deltaVector.y *= scale * magicNumber;

    return deltaVector;
}
