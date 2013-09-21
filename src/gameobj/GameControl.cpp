#include <inc/gameobj/GameControl.h>
#include <inc/col/Collision.h>
#include <inc/gameobj/ProgramControl.h>

#include <iostream>

GameControl::GameControl(ProgramControl* programControl){
    this->programControl = programControl;
}

GameControl::~GameControl(){
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

    music.openFromFile("res/music/music.ogg");

	pause = false;
	reset = false;
    firstGame = true;
}


void GameControl::update(float delta, sf::Vector2i &mousePosition){
    //Dev code
    sf::Keyboard keyboard;

    if(keyboard.isKeyPressed(sf::Keyboard::Space) && pause){
        music.stop();
        programControl->enterMenuState();
    }

 	if(keyboard.isKeyPressed(sf::Keyboard::Escape)){
        programControl->enterMenuState();
	}

    if(!pause){
        gridHandler     -> update(delta, mousePosition);
        friendHandler   -> update(delta);
        enemyHandler    -> update(delta);
        playerHandler   -> update(delta);
    }

    if(reset){
        gridHandler -> reset();
        friendHandler -> reset();
        enemyHandler -> reset();
        playerHandler -> reset();
        reset = false;
    }
}

void GameControl::render(sf::RenderWindow &window){

    gridHandler     -> render(window);
    friendHandler   -> render(window);
    enemyHandler    -> render(window);
    playerHandler   -> render(window);
}

void GameControl::resetGame(){
    pause = false;

    music.play();

    if(firstGame == false){
        reset = true;
    }else{
        firstGame = false;
    }
}


void GameControl::death(){
    pause = true;
    playerHandler -> death();
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
void GameControl::wallAdded(sf::Vector2i targetCoordinate){
    friendHandler->newTarget(targetCoordinate);
    playerHandler->wallAdded();
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
