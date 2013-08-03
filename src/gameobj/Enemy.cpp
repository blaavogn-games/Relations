#include <inc/gameobj/Enemy.h>

Enemy::Enemy(float x, float y){
	position.x = x;
	position.y = y;
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
