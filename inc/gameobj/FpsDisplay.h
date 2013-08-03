#ifndef FPSDISPLAY_H
#define FPSDISLAY_H
#include <inc/gameobj/GameObj.h>
#include <SFML/Graphics.hpp>

class FpsDisplay{

private:

    sf::Font font;
    int fps;
public:
    void init();
    void update(float delta);
    void render(sf::RenderWindow &window);
};


#endif
