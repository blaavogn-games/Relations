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
    std::deque<sf::Vector2i> finalPath;

    resetTiles(&endCoordinate);

    //In case player is on top of enemy
    if(startCoordinate.x == endCoordinate.x && startCoordinate.y == endCoordinate.y){
        finalPath.push_front(endCoordinate);
        return finalPath;
    }

    //Finding searchAxis (It is better for the enemies to prioritize the axis that has the largest delta)
    //Gives more natural movement
    int deltaX = std::fabs(startCoordinate.x - endCoordinate.x);
    int deltaY = std::fabs(startCoordinate.y - endCoordinate.y);
    searchAxis = (deltaX > deltaY) ? true : false ;

    gridHandler -> getGrid(&startCoordinate) -> setStartTile();

    finalPath = searchNoteRec(&startCoordinate, &endCoordinate);

    return finalPath;
}

void Pathfinder::resetTiles(sf::Vector2i* endCoordinate){

    //Resets all tiles to default, and calculates h to endCoordinate
    for(int y = 0; y < GameControl::GRIDY; y++){
        for(int x = 0; x < GameControl::GRIDX; x++){
            int heuristic = (std::abs(x - endCoordinate->x) + std::abs(y - endCoordinate->y));
            gridHandler -> getGrid(x,y) -> reset(heuristic);
        }
    }

    openList.clear();
}

std::deque<sf::Vector2i> Pathfinder::searchNoteRec(sf::Vector2i* searchCoordinate, sf::Vector2i* endCoordinate){

    GridTile* searchTile = gridHandler -> getGrid(searchCoordinate);

    //Puts searchTile on closedList
    searchTile -> closedList = true;

    //And in addition removes it from the openList (openList is a list, closedList an attribute)
    for(std::vector<sf::Vector2i>::iterator it = openList.begin(); it != openList.end(); ++it){
        if(searchCoordinate->x == it->x && searchCoordinate->y == it->y){
            openList.erase(it);
            break;
        }
    }

    if(searchAxis){
        calcTile(sf::Vector2i(searchCoordinate->x-1 , searchCoordinate->y) , searchTile); //Horizontal first
        calcTile(sf::Vector2i(searchCoordinate->x+1 , searchCoordinate->y) , searchTile);
        calcTile(sf::Vector2i(searchCoordinate->x , searchCoordinate->y - 1) , searchTile);
        calcTile(sf::Vector2i(searchCoordinate->x , searchCoordinate->y + 1) , searchTile);
    }else{
        calcTile(sf::Vector2i(searchCoordinate->x , searchCoordinate->y - 1) , searchTile); //Vertical first
        calcTile(sf::Vector2i(searchCoordinate->x , searchCoordinate->y + 1) , searchTile);
        calcTile(sf::Vector2i(searchCoordinate->x-1 , searchCoordinate->y) , searchTile);
        calcTile(sf::Vector2i(searchCoordinate->x+1 , searchCoordinate->y) , searchTile);
    }

    //Makes sure we stay within grid
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

void Pathfinder::calcTile(sf::Vector2i coordinate, GridTile* searchTile){
    //Checks if coordinate is within grid
    if(coordinate.x == -1 || coordinate.x == GameControl::GRIDX || coordinate.y == -1 || coordinate.y == GameControl::GRIDY){
        return;
    }

    GridTile* tile = gridHandler -> getGrid(&coordinate);

    if(! tile-> closedList){
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

/*bool Pathfinder::lineOfSight(sf::Vector2i* startCoordinate, sf::Vector2i endCoordinate){
//http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
//function line(x0, y0, x1, y1)
//   dx := abs(x1-x0)
//   dy := abs(y1-y0)
//   if x0 < x1 then sx := 1 else sx := -1
//   if y0 < y1 then sy := 1 else sy := -1
//   err := dx-dy
//
//   loop
//     plot(x0,y0)
//     if x0 = x1 and y0 = y1 exit loop
//     e2 := 2*err
//     if e2 > -dy then
//       err := err - dy
//       x0 := x0 + sx
//     end if
//     if x0 = x1 and y0 = y1 then
//       plot(x0,y0)
//       exit loop
//     end if
//     if e2 <  dx then
//       err := err + dx
//       y0 := y0 + sy
//     end if
//   end loop

    int x0 = startCoordinate->x;
    int y0 = startCoordinate->y;
    int x1 = endCoordinate->x;
    int y1 = endCoordinate->y;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    signed int stepX = (x0 < x1) ? 1 : -1;
    signed int stepY = (y0 < y1) ? 1 : -1;
    signed int err = dx - dy;

}*/
