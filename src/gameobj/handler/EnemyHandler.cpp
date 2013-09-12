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
	if(alarm){
        delete alarm;
	}
}

void EnemyHandler::init(){
    texEnemy.loadFromFile("res/img/enemies/enemy.png");

    alarm = new Alarm(this);
    alarm -> addTimer(0, 01);
}

void EnemyHandler::update(float delta){
	for(std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
		(*it)->update(delta);
	}
	alarm -> update(delta);
}

void EnemyHandler::render(sf::RenderWindow &window){
	for(std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it){
		(*it)->render(window);
	}
}

void EnemyHandler::alarmAction(int type){
    //Only 0 atm
    addEnemy();
}

//private
void EnemyHandler::addEnemy(){

    //Finding position version 1 (Should be points mutating into enemy)
    //Finde out which site to spawn on. 0=top, 1=bot, 2=left, 3right
    int site = rand() % 4;
    sf::Vector2i coordinate;
    coordinate.x = rand() % GameControl::GRIDX;
    coordinate.y = rand() % GameControl::GRIDY;

    switch(site){
        case 0:
            coordinate.y = 0;
        break;
        case 1:
            coordinate.y = GameControl::GRIDY - 1;
        break;
        case 2:
            coordinate.x = 0;
        break;
        case 3:
            coordinate.x = GameControl::GRIDX - 1;
        break;
    }

    sf::Vector2f position(coordinate.x * GameControl::GRIDSIZE  + 16, coordinate.y * GameControl::GRIDSIZE  + 16);

    Enemy* tempPointer = new Enemy(this,position, &texEnemy);
    tempPointer -> init();
    enemies.push_back(tempPointer);

    alarm -> addTimer(0,30);
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
