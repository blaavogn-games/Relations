#ifndef GRIDHANDLER_H
#define GRIDHANDLER_H

#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/Wall.h>
#include <inc/gameobj/Enemy.h>
#include <inc/container/CoordinateHash.h>
#include <inc/path/Pathfinder.h>
#include <inc/path/PathNote.h>

#include <unordered_map>
#include <vector>

//Forward declaration
class GameControl;

class GridHandler : protected GameObj{
    private:
        GameControl* gameControl;
        Pathfinder* pathfinder;

        sf::Sprite sprHighlight;
        sf::Texture txHighlight;

        bool firstMousePress;

        typedef std::unordered_map<sf::Vector2i, Wall*, CoordinateHash, CoordinateEquals> WallMap;

        WallMap walls;

        void attemptToAddWall(sf::Vector2i);
        void addWall(sf::Vector2i);

        sf::Vector2i getGridPosition(sf::Vector2i);
        sf::Vector2i toCoordinate(sf::Vector2i position);

    public:
        GridHandler(GameControl* gameControl);
        ~GridHandler();
        void init();
        void update( float delta , sf::Event &event, sf::Vector2i &mousePosition);
        void render(sf::RenderWindow &window);
        std::vector<Wall*> getSurWalls(sf::Vector2i &position);
        std::deque<sf::Vector2i> getPath(sf::Vector2i, sf::Vector2i);
};
#endif
