#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <inc/gameobj/GridTile.h>

#include <SFML/System.hpp>

#include <unordered_map>
#include <vector>
#include <deque>
#include <cmath>

//Forward declaration
class GridHandler;

class Pathfinder{
    private:
        GridHandler* gridHandler;

        bool searchAxis; //true = horizontal, false = vertical

        std::deque<sf::Vector2i> searchNoteRec(sf::Vector2i*, sf::Vector2i*);
        std::vector<sf::Vector2i> openList;

        void calcTile(sf::Vector2i, GridTile*);
        void resetTiles(sf::Vector2i*);
        sf::Vector2i findNextCoordinate();



    public:
        Pathfinder(GridHandler* gridHandler);
        ~Pathfinder();

        std::deque<sf::Vector2i> findPath(sf::Vector2i, sf::Vector2i);

};

#endif

