#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <inc/path/PathNote.h>

#include <SFML/System.hpp>

#include <unordered_map>
#include <vector>



class Pathfinder{
    private:

        PathNote* notes[25][19];

        std::vector<sf::Vector2i> searchNoteRec(sf::Vector2i, sf::Vector2i);

    public:
        Pathfinder();
        ~Pathfinder();
        std::vector<sf::Vector2i> findPath(sf::Vector2i startPoint, sf::Vector2i endPoint);

};

#endif

