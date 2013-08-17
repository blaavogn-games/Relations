#ifndef PATHNOTE_H
#define PATHNOTE_H

#include <SFML/System.hpp>
#include <iostream>
#include <deque>

class PathNote{
    private:
        const int MOVE = 10;
        bool closedList, wall;
        int heuristicValue, movementCost, combinedValue;
        sf::Vector2i coordinate;
        PathNote* parent;

    public:
        PathNote(sf::Vector2i coordinate, int heuristicValue, bool closedList = false, bool wall = false);
        ~PathNote();
        void getPathRec(std::deque<sf::Vector2i>*);

        bool calcNote(PathNote* searchPoint);
        int getMovementCost(){ return movementCost;}
        int getCombinedValue(){ return combinedValue;}
        sf::Vector2i* getCoordinate() {return &coordinate;}
        void setClosed(){closedList = true;}
        bool isClosedList(){return closedList;}
        bool isWall(){return wall;}

};

#endif

