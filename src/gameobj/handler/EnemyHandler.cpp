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
    texEnemy.loadFromFile("res/img/enemies/enemy.png");

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



void EnemyHandler::addEnemy(sf::Vector2f position){
    Enemy* tempPointer = new Enemy(this,position, &texEnemy);
    tempPointer -> init();
    enemies.push_back(tempPointer);
}

//set
void EnemyHandler::findNewPaths(){
    for(std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
		(*it)->findNewPath();
	}
}

//Get
std::vector<Enemy*> EnemyHandler::getEnemiesWithPathPoint(sf::Vector2i point){
	std::vector<Enemy*> enemiesWithPoint;

	for(std::vector<Enemy*>::iterator enemy_it = enemies.begin(); enemy_it != enemies.end(); ++enemy_it){
		std::deque<sf::Vector2i>* enemyPath = (*enemy_it)->getPath();

        for(std::deque<sf::Vector2i>::iterator path_it = enemyPath->begin(); path_it != enemyPath->end() ; ++path_it){
            if(point.x == (*path_it).x && point.y == (*path_it).y){
                enemiesWithPoint.push_back(*enemy_it);
                break;
            }
        }
	}

	return enemiesWithPoint;
}

std::deque<sf::Vector2i> EnemyHandler::getPath(sf::Vector2i coordinate){
    return gameControl->getPath(coordinate);
}
