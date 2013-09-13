#include <inc/gameobj/GameControl.h>
#include <inc/col/Collision.h>
#include <inc/gameobj/ProgramControl.h>

#include <iostream>

GameControl::GameControl(ProgramControl* programControl) : pause(false){
    this->programControl = programControl;
    pausePress = false;
    resetPress = false;
    firstGame = true;
}
GameControl::~GameControl(){
    clearGame();
}

void GameControl::init(){

    //enemyHandler dependent on gridHandler and player atm
	gridHandler = new GridHandler(this);
	gridHandler->init();

	friendHandler = new FriendHandler(this);
	friendHandler->init();

	playerHandler = new PlayerHandler(this);
	playerHandler->init();

	enemyHandler = new EnemyHandler(this);
	enemyHandler->init();

}

void GameControl::clearGame(){

    if(playerHandler){
		delete playerHandler;
	}
    if(enemyHandler){
		delete enemyHandler;
	}
    if(gridHandler){
        delete gridHandler;
    }
    if(friendHandler){
        delete friendHandler;
    }
}

void GameControl::update(float delta, sf::Vector2i &mousePosition){

    //Dev code
    sf::Keyboard keyboard;

    if(keyboard.isKeyPressed(sf::Keyboard::Space)){
        if(resetPress == false){
            resetGame();
        }
    }else{
        resetPress = false;
    }

 	if(keyboard.isKeyPressed(sf::Keyboard::Q)){
		if(pausePress == false){
            pausePress = true;
            pauseGame();
		}
	}else{
        pausePress = false;
	}

	if(!pause){
	    //std::cout << "Update" << std::endl;
        gridHandler     -> update(delta, mousePosition);
        friendHandler   -> update(delta);
        enemyHandler    -> update(delta);
        playerHandler   -> update(delta);
	}
}

void GameControl::render(sf::RenderWindow &window){

    if(!resetPress){
        //std::cout << "render" << std::endl;
        gridHandler     -> render(window);
        friendHandler   -> render(window);
        enemyHandler    -> render(window);
        playerHandler   -> render(window);
    }
}

void GameControl::resetGame(){
    resetPress = true;
    if(firstGame == false){
        clearGame();
        init();
    }else{
        firstGame = false;
    }
}

void GameControl::pauseGame(){
    pause = (pause) ? false : true;
}

void GameControl::enterMenuState(){
    programControl->enterMenuState();
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

void GameControl::addEnemy(sf::Vector2f position){
    enemyHandler->addEnemy(position);
}

//friendHandler
std::vector<Friend*>* GameControl::getFriends(){
    return friendHandler->getFriends();
}
void GameControl::friendsNewTarget(sf::Vector2i targetCoordinate){
    friendHandler->newTarget(targetCoordinate);
}

//GridHandler
std::vector<ColShape*> GameControl::getSurWalls(sf::Vector2i position){
    return gridHandler->getSurWalls(position);
}

std::deque<sf::Vector2i> GameControl::getPath(sf::Vector2i startPosition){
    return gridHandler->getPath(startPosition, getPlayerCoordinate());
}

GridTile* GameControl::getGrid(sf::Vector2i* coordinate){
    return gridHandler->getGrid(coordinate);
}

bool GameControl::isWall(int x, int y){
    return gridHandler->isWall(x,y);
}

//player
sf::Vector2i GameControl::getPlayerCoordinate(){
    return playerHandler -> getPlayerCoordinate();
}
