#include <inc/path/PathNote.h>

PathNote::PathNote(sf::Vector2i coordinate, int heuristicValue,  bool closedList, bool wall) : MOVE(10){
    this -> coordinate = coordinate;
    this -> heuristicValue = heuristicValue;
    this -> closedList = closedList;
    this -> wall = wall;
    parent = NULL;
    movementCost = 0;
}

PathNote::~PathNote(){
}

//Returns closedList value
bool PathNote::calcNote(PathNote *searchNote){
    if(closedList == false){
        if(parent == NULL || movementCost > parent->getMovementCost() + MOVE){
            parent = searchNote;
            movementCost = parent->getMovementCost() + MOVE;
            combinedValue = heuristicValue + movementCost;
            //std::cout << coordinate->x << " , " << coordinate->y << ": M=" << movementCost  << " H=" << heuristicValue << " C=" << combinedValue << std::endl;
        }
        return false;
    }else{
        return true;
    }
}

 void PathNote::getPathRec(std::deque<sf::Vector2i>* path){
    path->push_front(coordinate);
    if(parent == NULL){
        return;
    }else{
        parent->getPathRec(path);
    }
}
