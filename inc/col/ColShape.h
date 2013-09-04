#ifndef COLSHAPE_H
#define COLSHAPE_H
#include <inc/col/math/MathEssential.h>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>


/*All Shapes must be convex for collisiontest to work
Corners must be added clockwise as well. (ccw should work ass well just in "a->b->c->d format")
*/

/*
All corners are originally stored in relCorners
On rotation all corners are calculated into rotCorners, and seperationAxes are recalculated
On move all corners are calculated from rotCorners into absCorners
*/

class ColShape{
    private:
        sf::Vector2f position, center; //center = rotationPoint
        std::vector<sf::Vector2f> relCorners, rotCorners, absCorners, sepAxes;
        bool absCornersCalculated;
        float rotation;

        void calculateAbsCorners();
        void calculateSepAxes();
        bool sepAxisExists(sf::Vector2f newSepAxis);

        //For testing
        sf::Texture* texture;
        sf::Sprite* sprite;
    public:
        ColShape(sf::Vector2f, sf::Vector2f);
        virtual ~ColShape();
        void init();
        void render(sf::RenderWindow &window);

        void move(sf::Vector2f);
        void addCorner(sf::Vector2f);

        void setPosition(sf::Vector2f);
        void setRotation(float);

        std::vector<sf::Vector2f>* getCorners();
        std::vector<sf::Vector2f> getSepAxes();
        int getCorner(int, int);
};

#endif
