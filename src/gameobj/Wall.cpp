#include <inc/gameobj/Wall.h>
#include <iostream>

Wall::Wall(sf::Vector2f position){
    this->position = position;
}
Wall::~Wall(){
    if(colRectangle)
        delete colRectangle;
}
void Wall::init(){
    colRectangle = new ColRectangle(position,32,32);


	//Load data
	if (!texture.loadFromFile("res/img/wall.png"))
	{
	    std::cout << "FEJLFEJLFJELFJELFJLEFJEL" << std::endl;
		//UNHANDLED ERROR
	}

	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Wall::update(sf::Vector2i &mousePosition, float delta){

}

void Wall::render(sf::RenderWindow &window){

    //std::cout << "GGGG" << std::endl;
    window.draw(sprite);
}

ColRectangle* Wall::getCol(){
    return colRectangle;
}
