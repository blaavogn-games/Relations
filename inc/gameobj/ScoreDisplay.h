#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include <inc/gameobj/GameObj.h>
#include <SFML/Graphics.hpp>

class ScoreDisplay : public GameObj{

private:
    sf::Font font;
    sf::Text displayText, minorText;
    sf::Sprite bg;
    sf::Texture texBg;


    float fScore;
    int iScore;
    bool dead;

public:
    ScoreDisplay();
    ~ScoreDisplay();
    void init();
    void render(sf::RenderWindow &window);

    void death();
    void addScore(float points);
};


#endif

