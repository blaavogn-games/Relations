#ifndef WALLHANDLER_H
#define WALLHANDLER_H

#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/Wall.h>
#include <inc/container/CoordinateHash.h>
#include <inc/path/Pathfinder.h>
#include <inc/path/PathNote.h>

#include <unordered_map>
#include <vector>

class WallHandler : protected GameObj{
    private:
        Pathfinder* pathfinder;

        sf::Sprite sprHighlight;
        sf::Texture txHighlight;

        typedef std::unordered_map<sf::Vector2i, Wall*, CoordinateHash, CoordinateEquals> WallMap;

        WallMap walls;

        void addWall(sf::Vector2i);
        sf::Vector2i getGridPosition(int,int);
        sf::Vector2i toCoordinate(sf::Vector2i position);

    public:
        WallHandler();
        ~WallHandler();
        void init();
        void update( float delta , sf::Event &event, sf::Vector2i &mousePosition);
        void render(sf::RenderWindow &window);
        std::vector<Wall*> getSurWalls(sf::Vector2f &position);

};
#endif
