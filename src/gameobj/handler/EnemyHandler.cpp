#include "inc/gameobj/handler/EnemyHandler.h"
#include "inc/gameobj/GameControl.h"

EnemyHandler::EnemyHandler(GameControl* gameControl){
	this->gameControl = gameControl;
}

EnemyHandler::~EnemyHandler(){
    for(std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
        delete (*it);
    }
	enemies.clear();
}

void EnemyHandler::init(){

    enemies.push_back(new Enemy(this,sf::Vector2i(0,0)));

	for(std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
		(*it)->init();
	}

}

void EnemyHandler::update(float delta){
	for(std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
		(*it)->update(delta);
	}
}

void EnemyHandler::render(sf::RenderWindow &window){
	for(std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
		(*it)->render(window);
	}
}

std::deque<sf::Vector2i> EnemyHandler::getPath(sf::Vector2i position){
    return gameControl->getPath(position);
}
