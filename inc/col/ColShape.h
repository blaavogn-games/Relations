#ifndef COLSHAPE_H
#define COLSHAPE_H
#include <vector>
#include <SFML/Graphics.hpp>


/*All Shapes must be convex for collisiontest to work
Corners must be added clockwise as well. (ccw should work ass well just in "a->b->c->d format")
*/

class ColShape{
    private:
        sf::Vector2f position;
        std::vector<sf::Vector2f> relCorners, absCorners, sepAxes;
        bool absCornersCalculated, sepAxesCalculated;

        void calculateAbsCorners();
        void calculateSepAxes();
        bool sepAxisExists(sf::Vector2f newSepAxis);

    public:
        ColShape(sf::Vector2f);
        virtual ~ColShape(); // I am not sure about this being virtual
        void setPosition(sf::Vector2f);
        void move(sf::Vector2f);
        void addCorner(sf::Vector2f);
        std::vector<sf::Vector2f> getCorners();
        std::vector<sf::Vector2f> getSepAxes();
        int getCorner(int, int);
};

#endif
