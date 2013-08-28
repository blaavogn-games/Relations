#include <inc/gameobj/Point.h>

Point::Point() : RADIUS(4){}

Point::~Point(){
	if(colCircle){
		delete colCircle;
    }
}

void Point::init(sf::Texture* texture, sf::Vector2f position){
    this->position = position;
    sprPoint.setTexture(*texture);

    value = 20;

	colCircle = new ColCircle(position,RADIUS);
}

void Point::update(float delta){
    sprPoint.setPosition(position);
    colCircle->setPosition(position);
}

void Point::render(sf::RenderWindow &window){
    window.draw(sprPoint);
}


