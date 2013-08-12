#include <inc/gameobj/GameControl.h>
#include <inc/col/Collision.h>

#include <iostream>

GameControl::GameControl(){}
GameControl::~GameControl(){
	if(player)
		delete player;
	if(enemyHandler)
		delete enemyHandler;
    if(wallHandler)
        delete wallHandler;
}

void GameControl::init(){
    //enemyHandler dependent on wallhandler
	wallHandler = new WallHandler();
	wallHandler->init();

	player = new Player(this);
	player->init();

	enemyHandler = new EnemyHandler(this);
	enemyHandler->init();

}
void GameControl::update(float delta, sf::Event &event, sf::Vector2i &mousePosition){
	player->update(delta);
	enemyHandler->update(delta);
	wallHandler->update(delta, event, mousePosition);
}

void GameControl::render(sf::RenderWindow &window){
	player->render(window);
	enemyHandler->render(window);
	wallHandler->render(window);
}


std::vector<Enemy*>* GameControl::getEnemies(){
	return enemyHandler->getEnemies();
}

std::vector<Wall*> GameControl::getSurWalls(sf::Vector2i position){
    return wallHandler->getSurWalls(position);
}

std::deque<sf::Vector2i> GameControl::getPath(sf::Vector2i startPosition){
    return wallHandler->getPath(startPosition, player->getPosition());
}
