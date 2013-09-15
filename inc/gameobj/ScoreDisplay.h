#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/ScoreMsg.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ScoreDisplay : public GameObj{

private:
    sf::Font font;
    sf::Text displayText, minorText;
    sf::Sprite bg;
    sf::Texture texBg, scoreTex;
    sf::SoundBuffer scoreBuffer;
    sf::Sound scoreSound;
    std::vector<ScoreMsg*> scoreMsgs;

    float fScore;
    int iScore;
    bool dead;

public:
    ScoreDisplay();
    ~ScoreDisplay();
    void init();
    void update(float delta);
    void render(sf::RenderWindow &window);

    void death();
    void addScore(float points, sf::Vector2f);
};


#endif

