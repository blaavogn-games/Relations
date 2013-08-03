#include <inc/path/Pathfinder.h>

#include <inc/gameobj/GameControl.h>

#include <cmath>
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

std::vector<sf::Vector2i> Pathfinder::findPath(sf::Vector2i startPoint, sf::Vector2i endPoint){

    std::cout << "Finding path:" << std::endl;

//    notes[startPoint.x][startPoint.y] = new PathNote(startPoint, sf::Vector2i(-1, -1), true);


    return searchNoteRec(startPoint, endPoint);

}

std::vector<sf::Vector2i> Pathfinder::searchNoteRec(sf::Vector2i searchPoint, sf::Vector2i endPoint){
    std::vector<sf::Vector2i> ret;

    //Loops throught the surroinding grid
    signed int i = -1, j = -1, XMax = 1, YMax = 1;

    //Makes sure we stay within grid
    if(searchPoint.x == 0){
        i = 0;
    }else if(searchPoint.x == 24){
        XMax = 0;
    }

    if(searchPoint.y == 0){
        j = 0;
    }else if(searchPoint.y == 18){
        YMax = 0;
    }

    PathNote* searchNote = notes[searchPoint.x][searchPoint.y];

    for(signed int itX = i; itX <= XMax ; itX++){

        for(signed int itY = j; itY <= YMax ; itY++){


            sf::Vector2i curPoint(searchPoint.x + itX, searchPoint.y + itY);

            std::cout << curPoint.x << " , " << curPoint.y << std::endl;

            if(notes[curPoint.x][curPoint.y] == NULL ){
                int heuristicValue = std::abs(curPoint.x - searchPoint.x) + std::abs(curPoint.y - searchPoint.y);
                std::cout << "Opret" << std::endl;

                notes[curPoint.x][curPoint.y] = new PathNote(curPoint,heuristicValue);
            }
                notes[curPoint.x][curPoint.y]->calcNote(searchNote);
        }
//            notes.at(curPoint)->setValues()


    }
    return ret;
}
