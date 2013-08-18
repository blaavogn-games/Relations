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
    enemies.push_back(new Enemy(this,sf::Vector2i(0,10)));
    enemies.push_back(new Enemy(this,sf::Vector2i(10,0)));
    enemies.push_back(new Enemy(this,sf::Vector2i(5,12)));
    enemies.push_back(new Enemy(this,sf::Vector2i(15,15)));

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

std::deque<sf::Vector2i> EnemyHandler::getPath(sf::Vector2i position){
    return gameControl->getPath(position);
}
