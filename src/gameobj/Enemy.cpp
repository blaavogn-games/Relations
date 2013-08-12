#include <inc/gameobj/Enemy.h>
#include <inc/gameobj/handler/EnemyHandler.h>
#include <inc/gameobj/GameControl.h>
#include <inc/col/math/MathVector.h>


#include <cmath>
#include <iostream>

Enemy::Enemy(EnemyHandler* enemyHandler, sf::Vector2i startCoordinate){
    this->enemyHandler = enemyHandler;
	position.x = startCoordinate.x * GameControl::GRIDSIZE + GRIDOFFSET;
	position.y = startCoordinate.y * GameControl::GRIDSIZE + GRIDOFFSET;

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

    //Actual position
	path = enemyHandler->getPath(getPosition());
	path.pop_front();
    newTargetPoint();
}

void Enemy::update(float delta){

    if(std::fabs(targetPoint.x - position.x ) + std::fabs(targetPoint.y - position.y ) < 0.5f){
        path.pop_front();
        newTargetPoint();
    }

    position += MathVector::scale(movement,delta);

	//Redundant at this point
	sprite.setPosition(position);
	colCircle->setPosition(position);
}

void Enemy::render(sf::RenderWindow &window){
	window.draw(sprite);
}

void Enemy::newTargetPoint(){
	targetPoint.x = path.at(0).x * GameControl::GRIDSIZE + GRIDOFFSET;
	targetPoint.y = path.at(0).y * GameControl::GRIDSIZE + GRIDOFFSET;

    std::cout << "Target: " << targetPoint.x << " , " << targetPoint.y << std::endl;

    sf::Vector2f tempMovement;
    tempMovement.x = targetPoint.x - position.x;
    tempMovement.y = targetPoint.y - position.y;

	movement = MathVector::scale( MathVector::normalize(tempMovement) , SPEED);

}



sf::Vector2i Enemy::getPosition(){
    return sf::Vector2i( (int) position.x, (int) position.y);
}

