#include <inc/path/Pathfinder.h>
#include <inc/gameobj/GameControl.h>
#include <inc/gameobj/handler/GridHandler.h>

#include <cmath>
#include <iostream>
#include <climits>

Pathfinder::Pathfinder(GridHandler* gridHandler){
    this->gridHandler = gridHandler;
}

Pathfinder::~Pathfinder(){
}

std::deque<sf::Vector2i> Pathfinder::findPath(sf::Vector2i startCoordinate, sf::Vector2i endCoordinate){

    resetTiles(&endCoordinate);

    gridHandler -> getGrid(&startCoordinate) -> setStartTile();

    std::deque<sf::Vector2i> finalPath = searchNoteRec(&startCoordinate, &endCoordinate);

    if(finalPath.size() == 0){
        finalPath.push_back(endCoordinate);
    }

    return finalPath;
}

void Pathfinder::resetTiles(sf::Vector2i* endCoordinate){

    //Resets all tiles to default, and calculates h to endCoordinate
    for(int y = 0; y < GameControl::GRIDY; y++){
        for(int x = 0; x < GameControl::GRIDX; x++){
            int heuristic = (std::abs(x - endCoordinate->x) + std::abs(y - endCoordinate->y)) * 100;
            gridHandler -> getGrid(x,y) -> reset(heuristic);
        }
    }

    openList.clear();
}

std::deque<sf::Vector2i> Pathfinder::searchNoteRec(sf::Vector2i* searchCoordinate, sf::Vector2i* endCoordinate){

    GridTile* searchTile = gridHandler -> getGrid(searchCoordinate);

    //Puts searchTile on closedList
    searchTile -> setClosedList();

    //And in addition removes it from the openList (openList is a list, closedList an attribute)
    for(std::vector<sf::Vector2i>::iterator it = openList.begin(); it != openList.end(); ++it){
        if(searchCoordinate->x == it->x && searchCoordinate->y == it->y){
            openList.erase(it);
            break;
        }
    }

    //Makes sure we stay within grid
    if(searchCoordinate->x != 0){
        calcTile(gridHandler -> getGrid(searchCoordinate->x-1 , searchCoordinate->y) , searchTile );
    }

    if(searchCoordinate->x != 24){
        calcTile(gridHandler -> getGrid(searchCoordinate->x+1 , searchCoordinate->y) , searchTile );
    }

    if(searchCoordinate->y != 0){
        calcTile(gridHandler -> getGrid(searchCoordinate->x , searchCoordinate->y - 1) , searchTile );
    }

    if(searchCoordinate->y != 18){
        calcTile(gridHandler -> getGrid(searchCoordinate->x , searchCoordinate->y + 1) , searchTile );
    }

    sf::Vector2i nextCoordinate = findNextCoordinate();

    if(nextCoordinate.x == -1){
        std::deque<sf::Vector2i> emptyPath;
        return emptyPath;
    }

    if(endCoordinate->x == nextCoordinate.x && endCoordinate->y == nextCoordinate.y){
        std::deque<sf::Vector2i> finalPath;
        gridHandler -> getGrid(endCoordinate) -> getPathRec(&finalPath);
        return finalPath;
    }

    return searchNoteRec(&nextCoordinate, endCoordinate);
}

void Pathfinder::calcTile(GridTile* tile, GridTile* searchTile){
    if(! tile->onClosedList()){
        if(tile -> isFirstVisit()){
            openList.push_back(tile -> getCoordinate());
        }

        tile->calculate(searchTile);
    }
}


sf::Vector2i Pathfinder::findNextCoordinate(){
    sf::Vector2i returnCoordinate;
    int minValue = INT_MAX;

    if(openList.size() > 0){
        for(std::vector<sf::Vector2i>::iterator it = openList.begin(); it != openList.end(); ++it){
            int combinedValue = gridHandler -> getGrid((*it).x,(*it).y) -> getCombinedValue();
            if(combinedValue < minValue){
                minValue = combinedValue;
                returnCoordinate = (*it);
            }
        }
    }else{
        return sf::Vector2i(-1,-1);
    }

    return returnCoordinate;
}
