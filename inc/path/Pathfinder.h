#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <inc/path/PathNote.h>

#include <SFML/System.hpp>

#include <unordered_map>
#include <vector>



class Pathfinder{
    private:
        int tal = 0;
        PathNote* notes[25][19];

        std::vector<sf::Vector2i*> searchNoteRec(sf::Vector2i*, sf::Vector2i*);
        std::vector<PathNote*> openList;
        std::vector<sf::Vector2i> finalPath; //Burde nok være queue
        void calcPoint(sf::Vector2i* , sf::Vector2i*, PathNote*, sf::Vector2i);
        PathNote* nextNote();

    public:
        Pathfinder();
        ~Pathfinder();
        std::vector<sf::Vector2i*> findPath(sf::Vector2i* startPoint, sf::Vector2i* endPoint);

};

#endif

