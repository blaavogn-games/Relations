#include <inc/gameobj/ScoreMsg.h>

ScoreMsg::ScoreMsg() : SPEED(10){}

ScoreMsg::~ScoreMsg(){}

void ScoreMsg::init(sf::Vector2f position_p , sf::Texture *texture){

    sprite.setTexture(*texture);

    position.y = position_p.y - 40;
    position.x = position_p.x - 5;
    sprite.setPosition(position);

    timer = 0;
}

void ScoreMsg::update(float delta){
    position.y -= SPEED * delta;
    sprite.setPosition(position);
    timer += delta;
}

void ScoreMsg::render(sf::RenderWindow &window){
    window.draw(sprite);
}
