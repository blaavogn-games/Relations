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

void GridTile::init(sf::Texture (*textures)[6], sf::Vector2i coordinate){
    this->coordinate = coordinate;
    this->textures = textures;

    position.x = coordinate.x * GameControl::GRIDSIZE;
    position.y = coordinate.y * GameControl::GRIDSIZE;

    sprite.setTexture((*textures)[0]);
    sprite.setPosition(position);

    colShape = NULL;

    for(int i = 0; i < 4; i++){
        shadow[i] = 0;
    }
}

void GridTile::render(sf::RenderWindow &window){
    window.draw(sprite);
}

//public
void GridTile::setTexture(sf::Texture* texture){
    sprite.setTexture(*texture);
}

void GridTile::setShadow(int direction){

    if(shadow[direction] == 0 && !wall){
        shadow[direction] = 1;

        int sum = 0;
        for(int i = 0; i < 4; i++){
            sum += shadow[i];
        }

        setTexture( &(*textures)[sum] );
    }
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
