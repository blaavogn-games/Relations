#ifndef COLRECTANGLE_H
#define COLRECTANGLE_H
#include "ColShape.h"
#include <SFML/Graphics.hpp>

class ColRectangle : public ColShape{
public:
    ColRectangle(sf::Vector2f, float width, float height);
    ~ColRectangle();
};

#endif
