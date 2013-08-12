#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <inc/path/PathNote.h>

#include <SFML/System.hpp>

#include <unordered_map>
#include <vector>

//Forward declaration
class WallHandler;

class Pathfinder{
    private:
        int tal = 0;
        PathNote* notes[25][19];
        WallHandler* wallHandler;

        std::vector<sf::Vector2i*> searchNoteRec(sf::Vector2i*, sf::Vector2i*);
        std::vector<sf::Vector2i> openList;
        std::vector<sf::Vector2i> finalPath; //Burde nok være queue


        void calcPoint(sf::Vector2i* , sf::Vector2i*, PathNote*, sf::Vector2i);
        void clearNotes();
        PathNote* nextNote();

    public:
        void addWall(sf::Vector2i coordinate);
        Pathfinder(WallHandler* wallHandler);
        ~Pathfinder();
        std::vector<sf::Vector2i*> findPath(sf::Vector2i* startPoint, sf::Vector2i* endPoint);

};

#endif

