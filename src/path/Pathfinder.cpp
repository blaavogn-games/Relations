#include <inc/path/Pathfinder.h>
#include <inc/gameobj/GameControl.h>
#include <inc/gameobj/handler/WallHandler.h>

#include <cmath>
#include <queue>
#include <iostream>

Pathfinder::Pathfinder(WallHandler* wallHandler){

    this->wallHandler = wallHandler;

    for(int x = 0; x < 25; x++){
        for(int y = 0; y < 19; y++){
            notes[x][y] = NULL;
        }
    }
}

Pathfinder::~Pathfinder(){
    clearNotes();
}

std::vector<sf::Vector2i*> Pathfinder::findPath(sf::Vector2i* startPoint, sf::Vector2i* endPoint){

    std::cout << "Finding path:" << std::endl;

    clearNotes();

    notes[startPoint->x][startPoint->y] = new PathNote(*startPoint, 0);

    std::vector<sf::Vector2i*> returnVal = searchNoteRec(startPoint, endPoint);

    std::cout << "SLUT: " << tal << std::endl;
    notes[endPoint->x][endPoint->y]->getPathRec(&finalPath);


    for(std::vector<sf::Vector2i>::iterator it = finalPath.begin() ; it != finalPath.end() ; ++it){
        std::cout << it->x << " , " << it->y << std::endl;
    }

    return returnVal;
}

void Pathfinder::clearNotes(){

    std::cout << "Clearing notes:" << std::endl;

    for(int x = 0; x < 25; x++){
        for(int y = 0; y < 19; y++){
            if(notes[x][y] != NULL){

                std::cout << "Note: " << notes[x][y]->isWall() << std::endl;

                if(notes[x][y]->isWall() == false){
                    delete notes[x][y];
                    notes[x][y] = NULL;
                }else{
                    std::cout << "Wall not deleted!!!!!" << std::endl;

                }
            }
        }
    }

    openList.clear();
    finalPath.clear();
    tal = 0;
}

void Pathfinder::addWall(sf::Vector2i coordinate){

//    std::cout << "Adding Wall" << std::endl;
//    std::cout << coordinate.x << " , " << coordinate.y << std::endl;

    if(notes[coordinate.x][coordinate.y] != NULL){

        delete notes[coordinate.x][coordinate.y];

        notes[coordinate.x][coordinate.y] = NULL;
    }

    notes[coordinate.x][coordinate.y] = new PathNote((coordinate),0, true,true);


}

std::vector<sf::Vector2i*> Pathfinder::searchNoteRec(sf::Vector2i* searchPoint, sf::Vector2i* endPoint){
    std::vector<sf::Vector2i*> ret;

    std::cout << "Searching: " << searchPoint->x << " , " << searchPoint->y << std::endl;

    //Gets the searchNote, and puts it on the closed list, so the note doesn't search itself.
    PathNote* searchNote = notes[searchPoint->x][searchPoint->y];
    searchNote->setClosed();

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

    sf::Vector2i* nextPoint = (nextNote()->getCoordinate());


    if(endPoint->x == nextPoint->x && endPoint->y == nextPoint->y){

        return ret;
    }
    tal++;
    return searchNoteRec(nextPoint, endPoint);
}

void Pathfinder::calcPoint(sf::Vector2i* searchPoint, sf::Vector2i* endPoint, PathNote* searchNote, sf::Vector2i curPoint){
//

    //if a note doesn'r exist, it is created
    if(notes[curPoint.x][curPoint.y] == NULL ){
        int heuristicValue = std::abs(curPoint.x - endPoint->x) + std::abs(curPoint.y - endPoint->y);

        notes[curPoint.x][curPoint.y] = new PathNote(curPoint,heuristicValue  * 100);;
        if(curPoint.x == 1 && curPoint.y == 1){
            std::cout << notes[curPoint.x][curPoint.y] << std::endl;
        }

        openList.push_back(curPoint);
     }

    //calculates moveCost for point
    if(notes[curPoint.x][curPoint.y]-> getClosedList() == false){
        notes[curPoint.x][curPoint.y]->calcNote(searchNote);
    }
    // return false;
}

PathNote* Pathfinder::nextNote(){
    PathNote* returnValue;
    int minValue = 999999;
    for(std::vector<sf::Vector2i>::iterator it = openList.begin(); it != openList.end(); ++it){
   //     std::cout << (*it)->getCoordinate()->x <<  " , " << (*it)->getCoordinate()->y << std::endl;
        if(notes[(*it).x][(*it).y]->getClosedList()){
            //delete
            openList.erase(it);
        }else if(notes[(*it).x][(*it).y]->getCombinedValue() < minValue ){
            minValue = notes[(*it).x][(*it).y]->getCombinedValue();
            returnValue = notes[(*it).x][(*it).y];
        }
    }
    return returnValue;
}
