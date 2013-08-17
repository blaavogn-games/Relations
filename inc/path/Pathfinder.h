#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <inc/path/PathNote.h>

#include <SFML/System.hpp>

#include <unordered_map>
#include <vector>
#include <deque>

//Forward declaration
class GridHandler;

class Pathfinder{
    private:
        PathNote* notes[25][19];
        GridHandler* gridHandler;

        std::deque<sf::Vector2i> searchNoteRec(sf::Vector2i*, sf::Vector2i*);
        std::vector<sf::Vector2i> openList;

        void calcPoint(sf::Vector2i* , sf::Vector2i*, PathNote*, sf::Vector2i);
        void clearNotes();
        sf::Vector2i* getNextPoint();

    public:
        void addWall(sf::Vector2i coordinate);
        void removeWall(sf::Vector2i coordinate);
        Pathfinder(GridHandler* gridHandler);
        ~Pathfinder();
        std::deque<sf::Vector2i> findPath(sf::Vector2i* startPoint, sf::Vector2i* endPoint);

};

#endif

