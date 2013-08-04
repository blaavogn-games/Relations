#include <inc/path/Pathfinder.h>

#include <inc/gameobj/GameControl.h>

#include <cmath>
#include <queue>
#include <iostream>

Pathfinder::Pathfinder(){
    for(int x = 0; x < 25; x++){
        for(int y = 0; y < 19; y++){
            notes[x][y] = NULL;
        }
    }

}

Pathfinder::~Pathfinder(){
}

std::vector<sf::Vector2i*> Pathfinder::findPath(sf::Vector2i* startPoint, sf::Vector2i* endPoint){

    std::cout << "Finding path:" << std::endl;

    notes[startPoint->x][startPoint->y] = new PathNote(startPoint, 0);


    std::vector<sf::Vector2i*> returnVal = searchNoteRec(startPoint, endPoint);
    return returnVal;

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
        std::cout << "SLUT: " << tal << std::endl;
        notes[endPoint->x][endPoint->y]->getPathRec(&finalPath);

        std::cout << "REVERSE PATH:" << std::endl;

        for(std::vector<sf::Vector2i>::iterator it = finalPath.begin() ; it != finalPath.end() ; ++it){
            std::cout << it->x << " , " << it->y << std::endl;
        }


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


        PathNote* tempNote =  new PathNote(new sf::Vector2i(curPoint.x,curPoint.y),heuristicValue  * 100);

        notes[curPoint.x][curPoint.y] = tempNote;

        openList.push_back(tempNote);

     }

    //calculates moveCost for point
     notes[curPoint.x][curPoint.y]->calcNote(searchNote);
   // return false;
}

PathNote* Pathfinder::nextNote(){
    PathNote* returnValue;
    int minValue = 999999;
    for(std::vector<PathNote*>::iterator it = openList.begin(); it != openList.end(); ++it){
   //     std::cout << (*it)->getCoordinate()->x <<  " , " << (*it)->getCoordinate()->y << std::endl;
        if((*it)->getClosedList()){
            //delete
     //       openList.erase(it);
        }else if((*it)->getCombinedValue() < minValue ){
            minValue = (*it)->getCombinedValue();
            returnValue = (*it);
        }
    }
    return returnValue;
}
