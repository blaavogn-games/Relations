#include <inc/gameobj/GameControl.h>
#include <inc/gameobj/GridTile.h>

#include <climits>

GridTile::GridTile() : MOVE(10){
    wall = false;
    closedList = false;
    firstVisit = true;
}
GridTile::~GridTile(){
    if(colShape != NULL){
        delete colShape;
    }
}

void GridTile::init(sf::Texture* texture, sf::Vector2i coordinate){
    this->coordinate = coordinate;
    position.x = coordinate.x * GameControl::GRIDSIZE;
    position.y = coordinate.y * GameControl::GRIDSIZE;

    sprite.setTexture(*texture);
    sprite.setPosition(position);

    colShape = NULL;
}

void GridTile::render(sf::RenderWindow &window){
    window.draw(sprite);
}

//public
void GridTile::setTexture(sf::Texture* texture){
    sprite.setTexture(*texture);
}

//public
void GridTile::setWall(){
    wall = true;
    closedList = true;
    colShape = new ColRectangle(position, GameControl::GRIDSIZE, GameControl::GRIDSIZE);
}

void GridTile::setTempWall(){
    wall = true;
    closedList = true;
}

void GridTile::removeTempWall(){
    wall = false;
    closedList = false;
}


//public
void GridTile::reset(int heuristic){
    if(!wall){
        closedList = false;
        firstVisit = true;
        parent = NULL;
        movementCost = INT_MAX;
        heuristicValue = heuristic;
    }
}

//public
void GridTile::calculate(GridTile* searchTile){
    int searchMoveCost = searchTile -> getMovementCost() + MOVE;

    if(searchMoveCost < movementCost){
        movementCost = searchMoveCost;
        parent = searchTile;
        combinedValue = heuristicValue + movementCost;
    }

    firstVisit = false;
}

//public
void GridTile::setStartTile(){
    movementCost = 0;
}

//void GridTile::setClosedList(){
//    closedList = true;
//}

void GridTile::getPathRec(std::deque<sf::Vector2i>* path){
    path->push_front(coordinate);
    if(movementCost != 0){
        parent->getPathRec(path);
    }
}
