#include <inc/gameobj/Point.h>
#include <inc/gameobj/GameControl.h>

Point::Point() : RADIUS(7) , GRIDOFFSET(9){}

Point::~Point(){
	if(colCircle){
		delete colCircle;
    }
}

void Point::init(sf::Texture* texture, sf::Vector2i coordinate){
    this->coordinate = coordinate;
    position.x = coordinate.x * GameControl::GRIDSIZE + GRIDOFFSET;
    position.y = coordinate.y * GameControl::GRIDSIZE + GRIDOFFSET;

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

float Point::getValue(){
    return value;
}


