#include <inc/gameobj/GameControl.h>
#include <inc/col/Collision.h>

#include <iostream>

GameControl::GameControl() : pause(false){
    pausePress = false;
    resetPress = false;
}
GameControl::~GameControl(){
    clearGame();
}

void GameControl::init(){

	pointHandler = new PointHandler(this);
	pointHandler->init();

    //enemyHandler dependent on gridHandler and player atm
	gridHandler = new GridHandler(this);
	gridHandler->init();

	player = new Player(this);
	player->init();

	enemyHandler = new EnemyHandler(this);
	enemyHandler->init();

}

void GameControl::clearGame(){
    if(player){
		delete player;
	}
    if(enemyHandler){
		delete enemyHandler;
	}
    if(gridHandler){
        delete gridHandler;
    }
    if(pointHandler){
        delete pointHandler;
    }
}

void GameControl::update(float delta, sf::Event &event, sf::Vector2i &mousePosition){

    //Dev code
    sf::Keyboard keyboard;

    if(keyboard.isKeyPressed(sf::Keyboard::Space)){
        if(resetPress == false){
            resetPress = true;
            resetGame();
        }
    }else{
        resetPress = false;
    }

 	if(keyboard.isKeyPressed(sf::Keyboard::Q)){
		if(pausePress == false){
            pause = (pause) ? false : true;
            pausePress = true;
		}
	}else{
        pausePress = false;
	}

	if(!pause){
        gridHandler     -> update(delta, event, mousePosition);
        pointHandler    -> update(delta);
        enemyHandler    -> update(delta);
        player          -> update(delta);
	}
}

void GameControl::render(sf::RenderWindow &window){
    gridHandler     -> render(window);
    pointHandler    -> render(window);
    enemyHandler    -> render(window);
    player          -> render(window);
}

void GameControl::resetGame(){
    clearGame();
    init();
}

//Enemyhandler pipeline
void GameControl::enemiesFindNewPath(){
    enemyHandler -> findNewPaths();
}

std::vector<Enemy*> GameControl::getEnemiesWithPathPoint(sf::Vector2i point){
    return enemyHandler -> getEnemiesWithPathPoint(point);
}

std::vector<Enemy*>* GameControl::getEnemies(){
	return enemyHandler->getEnemies();
}

//PointHandler
std::vector<Point*>* GameControl::getPoints(){
    return pointHandler->getPoints();
}

//GridHandler
std::vector<ColShape*> GameControl::getSurWalls(sf::Vector2i position){
    return gridHandler->getSurWalls(position);
}

std::deque<sf::Vector2i> GameControl::getPath(sf::Vector2i startPosition){
    return gridHandler->getPath(startPosition, player->getCoordinate());
}

GridTile* GameControl::getGrid(sf::Vector2i* coordinate){
    return gridHandler->getGrid(coordinate);
}

//player
sf::Vector2i GameControl::getPlayerCoordinate(){
    return player -> getCoordinate();
}
