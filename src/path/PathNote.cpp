#include <inc/path/PathNote.h>
#include <iostream>

PathNote::PathNote(sf::Vector2i* coordinate, int heuristicValue,  bool closedList){

    this -> coordinate = coordinate;
    this -> heuristicValue = heuristicValue;
    this -> closedList = closedList;
    parent = NULL;
    movementCost = 0;
}

//Returns closedList value
bool PathNote::calcNote(PathNote *searchNote){
    if(closedList == false){
        if(parent == NULL || movementCost > parent->getMovementCost() + MOVE){
            parent = searchNote;
            movementCost = parent->getMovementCost() + MOVE;
            combinedValue = heuristicValue + movementCost;

            std::cout << coordinate->x << " , " << coordinate->y << ": M=" << movementCost  << " H=" << heuristicValue << " C=" << combinedValue << std::endl;


        }


        return false;
    }else{
        return true;
    }
}

 void PathNote::getPathRec(std::vector<sf::Vector2i>* path){
    path->push_back(*coordinate);
    if(parent == NULL){
        return;
    }else{
        parent->getPathRec(path);
    }
}
