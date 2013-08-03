#include <inc/path/PathNote.h>

PathNote::PathNote(sf::Vector2i coordinate, int heuristicValue, bool closedList){
    this -> coordinate = coordinate;
    this -> heuristicValue = heuristicValue;
    this -> closedList = closedList;
    movementCost = 0;
}

void PathNote::calcNote(PathNote *searchNote){


}
