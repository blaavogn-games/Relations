#ifndef PATHNOTE_H
#define PATHNOTE_H

#include <SFML/System.hpp>


class PathNote{
    private:
        const int MOVE = 10;
        bool closedList;
        int heuristicValue, movementCost, combinedValue;
        sf::Vector2i* coordinate;
        PathNote* parent;

    public:
        PathNote(sf::Vector2i* coordinate, int heuristicValue, bool closedList = false);


        bool calcNote(PathNote* searchPoint);
        int getMovementCost(){ return movementCost;}
        int getCombinedValue(){ return combinedValue;}
        sf::Vector2i* getCoordinate() {return coordinate;}
        void setClosed(){closedList = true;}
        bool getClosedList(){return closedList;}

};

#endif

