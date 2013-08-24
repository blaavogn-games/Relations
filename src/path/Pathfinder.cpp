#include <inc/path/Pathfinder.h>
#include <inc/gameobj/GameControl.h>
#include <inc/gameobj/handler/GridHandler.h>

#include <cmath>
#include <iostream>
#include <climits>

Pathfinder::Pathfinder(GridHandler* gridHandler){
    this->gridHandler = gridHandler;

    for(int x = 0; x < 25; x++){
        for(int y = 0; y < 19; y++){
            notes[x][y] = NULL;
        }
    }
}

Pathfinder::~Pathfinder(){
    clearNotes();
}

std::deque<sf::Vector2i> Pathfinder::findPath(sf::Vector2i* startPoint, sf::Vector2i* endPoint){
    clearNotes();

    notes[startPoint->x][startPoint->y] = new PathNote(*startPoint, 0);

    std::deque<sf::Vector2i> finalPath = searchNoteRec(startPoint, endPoint);

    return finalPath;
}

void Pathfinder::clearNotes(){
    for(int x = 0; x < 25; x++){
        for(int y = 0; y < 19; y++){
            if(notes[x][y] != NULL){
                if(notes[x][y]->isWall() == false){
                    delete notes[x][y];
                    notes[x][y] = NULL;
                }
            }
        }
    }

    openList.clear();
}

void Pathfinder::addWall(sf::Vector2i coordinate){

    if(notes[coordinate.x][coordinate.y] != NULL){

        delete notes[coordinate.x][coordinate.y];

        notes[coordinate.x][coordinate.y] = NULL;
    }

    notes[coordinate.x][coordinate.y] = new PathNote((coordinate),0, true,true);
}

void Pathfinder::removeWall(sf::Vector2i coordinate){

    if(notes[coordinate.x][coordinate.y] != NULL){

        delete notes[coordinate.x][coordinate.y];

        notes[coordinate.x][coordinate.y] = NULL;
    }

}

std::deque<sf::Vector2i> Pathfinder::searchNoteRec(sf::Vector2i* searchPoint, sf::Vector2i* endPoint){
    //Gets the searchNote, and puts it on the closed list, so the note doesn't search itself.
    PathNote* searchNote = notes[searchPoint->x][searchPoint->y];
    searchNote->setClosed();


    for(std::vector<sf::Vector2i>::iterator it = openList.begin(); it != openList.end(); ++it){
        if(searchPoint->x == it->x && searchPoint->y == it->y){
            openList.erase(it);
            break;
        }
    }

    //Makes sure we stay within grid
    if(searchPoint->x != 0){
        calcPoint(searchPoint, endPoint, searchNote,  sf::Vector2i(searchPoint->x -1 , searchPoint->y ));
    }

    if(searchPoint->x != 24){
        calcPoint(searchPoint, endPoint, searchNote, sf::Vector2i(searchPoint->x +1 , searchPoint->y ));
    }

    if(searchPoint->y != 0){
        calcPoint(searchPoint, endPoint, searchNote, sf::Vector2i(searchPoint->x , searchPoint-> y -1 ));
    }
    if(searchPoint->y != 18){
        calcPoint(searchPoint, endPoint, searchNote, sf::Vector2i(searchPoint->x , searchPoint-> y  +1 ));
    }

    sf::Vector2i* nextPoint = getNextPoint();

    if(nextPoint == NULL){
        std::deque<sf::Vector2i> emptyPath;
        return emptyPath;
    }

    if(endPoint->x == nextPoint->x && endPoint->y == nextPoint->y){
        std::deque<sf::Vector2i> finalPath;
        notes[endPoint->x][endPoint->y]->getPathRec(&finalPath);
        return finalPath;
    }

    return searchNoteRec(nextPoint, endPoint);
}

void Pathfinder::calcPoint(sf::Vector2i* searchPoint, sf::Vector2i* endPoint, PathNote* searchNote, sf::Vector2i curPoint){
//

    //if a note doesn'r exist, it is created
    if(notes[curPoint.x][curPoint.y] == NULL ){
        int heuristicValue = std::abs(curPoint.x - endPoint->x) + std::abs(curPoint.y - endPoint->y);

        notes[curPoint.x][curPoint.y] = new PathNote(curPoint,heuristicValue  * 100);;

        openList.push_back(curPoint);
     }

    //calculates moveCost for point
    if(notes[curPoint.x][curPoint.y]-> isClosedList() == false){
        notes[curPoint.x][curPoint.y]->calcNote(searchNote);
    }
}

sf::Vector2i* Pathfinder::getNextPoint(){
    PathNote* returnNote;
    int minValue = INT_MAX;

    if(openList.size() > 0){
        for(std::vector<sf::Vector2i>::iterator it = openList.begin(); it != openList.end(); ++it){
            //std::cout << (*it).x << " , " << (*it).y << std::endl;
            if(notes[(*it).x][(*it).y]->isClosedList() && !notes[(*it).x][(*it).y]->isWall()){
                //delete
                openList.erase(it);
            }else if(notes[(*it).x][(*it).y]->getCombinedValue() < minValue ){
                minValue = notes[(*it).x][(*it).y]->getCombinedValue();
                returnNote = notes[(*it).x][(*it).y];
            }
        }
    }else{
        return NULL;
    }

    return returnNote->getCoordinate();
}
