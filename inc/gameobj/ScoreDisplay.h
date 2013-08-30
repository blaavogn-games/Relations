#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include <inc/gameobj/GameObj.h>
#include <SFML/Graphics.hpp>

class ScoreDisplay : public GameObj{

private:
    sf::Font font;
    sf::Text displayText;

    float fScore;
    int iScore;

public:
    ScoreDisplay();
    ~ScoreDisplay();
    void init();
    void update(float delta);
    void render(sf::RenderWindow &window);

    void addScore(float points);
};


#endif

