#include <inc/gameobj/Player.h>
#include <inc/gameobj/GameControl.h>
#include <inc/gameobj/handler/PlayerHandler.h>

#include <iostream>

Player::Player(PlayerHandler* playerHandler, GameControl* gameControl, sf::Vector2f position, sf::Texture* texture) :
        PersonBase(position, texture){
    this->playerHandler = playerHandler;
	this->gameControl = gameControl;
}
Player::~Player(){
}

void Player::init(){
    PersonBase::init();

	//Variables
	speed = 22;
    previousCoordinate = getCoordinate();
}


void Player::update(float delta){
    PersonBase::update(delta);

	//Two phases
	//1. Movement
	//2. CollisionChecking
    sf::Keyboard keyboard;

	//Movement
	sf::Vector2f curMovement(0,0);

	float deltaSpeed = speed * delta;

	if(keyboard.isKeyPressed(sf::Keyboard::A) && position.x > 0 + CENTER.x){
		curMovement.x -= deltaSpeed;
	}
	if(keyboard.isKeyPressed(sf::Keyboard::D)  && position.x < 800 - CENTER.x){
		curMovement.x += deltaSpeed;
	}
	if(keyboard.isKeyPressed(sf::Keyboard::W) && position.y > 0 + CENTER.y){
		curMovement.y -= deltaSpeed;
	}
	if(keyboard.isKeyPressed(sf::Keyboard::S) && position.y < 600 - CENTER.x){
		curMovement.y += deltaSpeed;
	}

    //Diaognal movement not faster
    if((curMovement.x != 0) ^ (curMovement.y != 0)){ //Going sideways
        curMovement.x *= 1.4f;
        curMovement.y *= 1.4f;
    }

	position += curMovement;
	col->setPosition(position);

    calculateSprite(delta, &curMovement);

	//Collision wall
    std::vector<ColShape*> surWalls = gameControl->getSurWalls(previousCoordinate);

    int ventil = 0;
    while(collisionHandler(surWalls) && ventil < 2){
        ventil++;
    }

    setPosition(position);

    //Collision friend
    std::vector<Friend*>* friends = gameControl->getFriends();
    std::vector<Friend*>::iterator friendsIt = friends->begin();

    sf::Vector2f notUsedReturn;

    while(friendsIt != friends->end()){
        if(Collision::doesCollide((*friendsIt)->getCol() , col , &notUsedReturn)){

            playerHandler->addScore((*friendsIt)->getValue());

            delete (*friendsIt);
            friendsIt = friends -> erase (friendsIt);
        }else{
            friendsIt++;
        }

    }

    //Collision enemy
	std::vector<Enemy*>* enemies = gameControl->getEnemies();
    std::vector<Enemy*>::iterator it = enemies->begin();

    while(it != enemies->end()){

        if(Collision::doesCollide((*it)->getCol(), col, &notUsedReturn )){
            delete (*it);
            it = enemies -> erase(it);
            if(playerHandler -> looseLife()){ //Returns true on dead
                std::cout << "DØØØØØØØØØD" << std::endl;
                gameControl -> resetGame();
                return; //Exits update
            }
        }else{
            it++;
        }

    }

    //Check if player moves into a new coordinate, if player does, enemies has to find new path
    sf::Vector2i currentCoordinate = getCoordinate();
    if(currentCoordinate.x != previousCoordinate.x || currentCoordinate.y != previousCoordinate.y){
        //Message enemies about new coordinate
        gameControl -> enemiesFindNewPath();
    }
    previousCoordinate = currentCoordinate;
}

bool Player::collisionHandler(std::vector<ColShape*> surWalls){
    bool res = false;

    for(std::vector<ColShape*>::iterator it = surWalls.begin(); it != surWalls.end(); it++){
        sf::Vector2f returnVector;
        if(Collision::doesCollide(col, *it , &returnVector)){
            position += returnVector;
            col->setPosition(position);
            res = true;
        }

    }
    return res;
}


