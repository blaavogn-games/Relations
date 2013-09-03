#include "inc/col/Collision.h"

bool Collision::doesCollide(ColCircle c1, ColCircle c2){
	sf::Vector2f pos1 = c1.getPosition();
	sf::Vector2f pos2 = c2.getPosition();

	if(MathVector::distance(pos1,pos2) > (c1.getRadius() + c2.getRadius())){
		return false;
	}
	return true;
}


//Shape - Shape
bool Collision::doesCollide(ColShape* shape1, ColShape* shape2, sf::Vector2f* returnVector){

    //The return vector doeas not work if 1 of the polys is inside the other
    std::vector<sf::Vector2f> allSepAxes, s1SepAxes, s2SepAxes;
    s1SepAxes = shape1->getSepAxes();
    s2SepAxes = shape2->getSepAxes();


    //Finding unique seperating axes
    for(std::vector<sf::Vector2f>::iterator it = s1SepAxes.begin(); it != s1SepAxes.end(); ++it){
        if(doesAxisExist((*it),&allSepAxes) == false){
            allSepAxes.push_back(*it);
        }
    }

    for(std::vector<sf::Vector2f>::iterator it = s2SepAxes.begin(); it != s2SepAxes.end(); ++it){
        if(doesAxisExist((*it),&allSepAxes) == false){
            allSepAxes.push_back(*it);
        }
    }

    //The minimum overlap found across sepAxes
    float minOverlap = FLT_MAX;



    //Checkin each sepAxis
    for(std::vector<sf::Vector2f>::iterator it = allSepAxes.begin(); it != allSepAxes.end(); ++it){
        //Checking which axes to compare on -- X-axis unless very steep axis
        bool compAxisX = ((*it).x > 0.1 || (*it).x < -0.1) ? true : false; //true = x-axis

        //Gets min & max projection
        std::vector<sf::Vector2f> shape1Proj = getOuterProjection((*it), shape1->getCorners(), compAxisX);
        std::vector<sf::Vector2f> shape2Proj = getOuterProjection((*it), shape2->getCorners(), compAxisX);


        //Finds the two delta vectors shape2.min - shape1.max & shape2.max - shape1.min
        sf::Vector2f delta1(shape2Proj.at(0).x - shape1Proj.at(1).x , shape2Proj.at(0).y - shape1Proj.at(1).y);
        sf::Vector2f delta2(shape2Proj.at(1).x - shape1Proj.at(0).x , shape2Proj.at(1).y - shape1Proj.at(0).y);

        //This is in reality the actual collision check step.
        //I am checking whether the two outer projections overlap
        //For some reason I can do this, by looking at the delta vectors
        // It was kind of cool when I thought of it, now I don't remember why it works
        if(compAxisX && (delta1.x > 0 || delta2.x < 0)){
            return false;                       //If there isn't collision on all axis, there is no collision
        }else if(!compAxisX && (delta1.y > 0 || delta2.y < 0)){
            return false;
        }


        if(MathVector::lengthSquared(&delta1) < minOverlap ){
            returnVector->x = delta1.x * 1.0001f;;
            returnVector->y = delta1.y * 1.0001f;;
            minOverlap = MathVector::lengthSquared(&delta1);
        }
        if(MathVector::lengthSquared(&delta2) < minOverlap ){
            returnVector->x = delta2.x * 1.0001f;;
            returnVector->y = delta2.y * 1.0001f;
            minOverlap = MathVector::lengthSquared(&delta2);
        }

    }

    return true;

}

//Circle - Shape
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
    std::vector<sf::Vector2f>* corners = shape->getCorners();
    float cornerSum = corners->size();

    int closestCornerNum = 0;
    float closestDistance = MathVector::distance(circleCenter, corners->at(0));

    for(int i = 1; i < cornerSum; i++){
        float distance = MathVector::distance(circleCenter, corners->at(i));

        if(distance < closestDistance ){
            closestCornerNum = i;
            closestDistance = distance;
        }
    }

    //2
    sf::Vector2f closestCorner = corners->at(closestCornerNum);
    sf::Vector2f prevCorner = corners->at(shape->getCorner(closestCornerNum,-1));
    sf::Vector2f nextCorner = corners->at(shape->getCorner(closestCornerNum,1));

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
            *returnVector = Collision::movePFromP(circleCenter , corners->at(closestCornerNum), circle->getRadius());
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


std::vector<sf::Vector2f> Collision::getOuterProjection(sf::Vector2f axis, std::vector<sf::Vector2f>* corners, bool compAxisX) {
    //Returns the min & max projections
    std::vector<sf::Vector2f> outerProjections;
    outerProjections.resize(2);

    float max = -FLT_MAX, min = FLT_MAX;

    for (std::vector<sf::Vector2f>::iterator it = corners->begin(); it != corners->end(); ++it) {

        sf::Vector2f projection;

        //Calculates dot product
        float dotProduct = axis.x * (*it).x + axis.y * (*it).y;

        //Calculates projection
        projection.x = axis.x * dotProduct; //axis is normalized so only dotProduct is needed
        projection.y = axis.y * dotProduct;

        float f = (compAxisX) ? projection.x : projection.y ;

        //Checks projection to see if it is the current min or max
        if (min > f) {
            min = f;
            outerProjections.at(0) = projection;
        }
        if (max < f) {
            max = f;
            outerProjections.at(1) = projection;
        }
    }
    return outerProjections;
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

bool Collision::doesAxisExist(sf::Vector2f axis, std::vector<sf::Vector2f>* axesVector){
    for(std::vector<sf::Vector2f>::iterator it = axesVector->begin(); it != axesVector->end(); ++it){
        if(MathEssential::fIsEqual(it->x,axis.x) && MathEssential::fIsEqual(it->y,axis.y)){
            return true;
        }
    }
    return false;
}
