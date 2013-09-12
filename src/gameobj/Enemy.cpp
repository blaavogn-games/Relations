#include <inc/gameobj/Enemy.h>
#include <inc/gameobj/handler/EnemyHandler.h>
#include <inc/gameobj/GameControl.h>
#include <inc/col/math/MathVector.h>

#include <cmath>
#include <iostream>

Enemy::Enemy(EnemyHandler* enemyHandler, sf::Vector2f position, sf::Texture* texture) :
        PersonBase(position, texture) , SPEED(28){
    this->enemyHandler = enemyHandler;
	this->position = position;
}

Enemy::~Enemy(){

}

void Enemy::init(){
    PersonBase::init();

	texPath.loadFromFile("res/img/temp_path.png");

    sprPath.setTexture(texPath);

    setPosition(position);

    //Actual position
    findNewPath();
}

void Enemy::update(float delta){

    if(std::fabs(targetPoint.x - position.x) + std::fabs(targetPoint.y - position.y) < 1){

        newTargetPoint();
    }

    position += MathVector::scale(movement,delta);

    setPosition(sf::Vector2f(position.x, position.y));
    calculateSprite(delta, &movement);
}

void Enemy::render(sf::RenderWindow &window){

	//Just for testing
	for(std::deque<sf::Vector2i>::iterator it = path.begin(); it != path.end(); ++it){
        sprPath.setPosition((it)->x * 32 , (it)->y * 32);
        window.draw(sprPath);
	}

    PersonBase::render(window);

}

void Enemy::findNewPath(){
    setPath(enemyHandler->getPath(getCoordinate()));
}

void Enemy::setPath(std::deque<sf::Vector2i> newPath){

    path = newPath;

    if(std::fabs(path.at(0).x - position.x ) + std::fabs(path.at(0).y - position.y ) < 10.0f){
        if(path.size() > 1){
            path.pop_front();
        }
    }

    newTargetPoint();
}

void Enemy::newTargetPoint(){

    if(path.size() > 1){
        path.pop_front();

        targetPoint.x = path.at(0).x * GameControl::GRIDSIZE + 16;
        targetPoint.y = path.at(0).y * GameControl::GRIDSIZE + 16;

        sf::Vector2f tempMovement;
        tempMovement.x = targetPoint.x - position.x;
        tempMovement.y = targetPoint.y - position.y;

        movement = MathVector::scale( MathVector::normalize(tempMovement) , 10);
    }
}
