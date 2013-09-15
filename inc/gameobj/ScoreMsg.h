#ifndef SCOREMSG_H
#define SCOREMSG_H

#include <SFML/Graphics.hpp>

#include <inc/gameobj/GameObj.h>

class ScoreMsg : public GameObj{

private:
    sf::Sprite sprite;
    sf::Vector2f position;
    const int SPEED;

public:
    float timer; //Seems easier than using alarm, for this purpose eache ScoreMsg is to some extend a timer
    ScoreMsg();
    ~ScoreMsg();

    void init(sf::Vector2f position, sf::Texture* texture);
    void update(float delta);
    void render(sf::RenderWindow &window);
};


#endif
