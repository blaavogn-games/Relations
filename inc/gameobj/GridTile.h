#ifndef GRIDTILE_H
#define GRIDTILE_H
#include <SFML/Graphics.hpp>

#include <inc/gameobj/GameObj.h>
#include <inc/col/ColRectangle.h>

#include <deque>

class GridTile : public GameObj{
    private:
        const int MOVE;

        sf::Sprite sprite;
        sf::Vector2i coordinate;
        sf::Vector2f position; //In reality gridPos

        bool wall, firstVisit;
        int heuristicValue, movementCost, combinedValue;

        ColShape* collision;
        GridTile* parent;

    public:
        bool closedList;

        GridTile();
        ~GridTile();

        void init(sf::Texture*, sf::Vector2i);
        void render(sf::RenderWindow &window);

        void setTexture(sf::Texture* texture);

        void reset(int);
        void calculate(GridTile*);
        void setStartTile();
        bool isFirstVisit(){ return firstVisit;}
        int getMovementCost(){ return movementCost;}
        int getCombinedValue(){ return combinedValue;}
        void getPathRec(std::deque<sf::Vector2i>*);


        sf::Vector2i getCoordinate(){return coordinate; }

        void setTempWall();
        void removeTempWall();

        void setWall();
        bool isWall(){ return wall; }
        ColShape* getCollision(){return collision;}



};


#endif
