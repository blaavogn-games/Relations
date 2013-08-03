#ifndef PATHNOTE_H
#define PATHNOTE_H

#include <SFML/System.hpp>


class PathNote{
    private:
        bool closedList;
        int heuristicValue, movementCost, combinedValue;
        sf::Vector2i coordinate;

    public:
        PathNote(sf::Vector2i coordinate, int heuristicValue, bool closedList = false);


        void calcNote(PathNote* searchPoint);

};

#endif

