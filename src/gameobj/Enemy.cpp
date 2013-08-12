#include <inc/gameobj/Enemy.h>

Enemy::Enemy(sf::Vector2i startCoordinate){
	position.x = startCoordinate.x * 32 + GRIDOFFSET;
	position.y = startCoordinate.y * 32 + GRIDOFFSET;
}
Enemy::~Enemy(){
	if(colCircle)
		delete colCircle;
}

void Enemy::init(){


	colCircle = new ColCircle(position,8);

	if (!texture.loadFromFile("res/img/enemy.png"))
	{
		//std::cout << "Error while loading player texture" << std::endl;
	}
	sprite.setTexture(texture);
}

void Enemy::update(float delta){
	//Redundant at this point
	sprite.setPosition(position);
	colCircle->setPosition(position);
}

void Enemy::render(sf::RenderWindow &window){
	window.draw(sprite);
}
