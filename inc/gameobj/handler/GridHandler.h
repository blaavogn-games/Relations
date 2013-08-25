#ifndef GRIDHANDLER_H
#define GRIDHANDLER_H

#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/Enemy.h>
#include <inc/gameobj/GridTile.h>
#include <inc/path/Pathfinder.h>
#include <inc/path/PathNote.h>


#include <unordered_map>
#include <vector>

/*Names might be messed up atm, but in general.

position = Actual position
gridPoisition = position rounded down to nearest 32
coordinate = gridposition / 32 */

//Forward declaration
class GameControl;

class GridHandler : protected GameObj{
    private:
        GameControl* gameControl;
        Pathfinder* pathfinder;

        GridTile* grid[25][19];
        sf::Texture gridTextures[6]; //0 to 4 different shadows, 5 = wall

        sf::Sprite sprHighlight;
        sf::Texture txHighlight;

        bool firstMousePress;


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

        std::vector<ColShape*> getSurWalls(sf::Vector2i &position);
        std::deque<sf::Vector2i> getPath(sf::Vector2i, sf::Vector2i);
        GridTile* getGrid(sf::Vector2i* coordinate){ return grid[coordinate->x][coordinate->y];}
        GridTile* getGrid(int x, int y){return grid[x][y];}
};
#endif
