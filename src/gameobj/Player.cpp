#include <inc/gameobj/Player.h>
#include <inc/gameobj/GameControl.h>
#include <inc/gameobj/handler/PlayerHandler.h>

#include <iostream>

Player::Player(PlayerHandler* playerHandler, GameControl* gameControl, sf::Vector2f position, sf::Texture* texture) :
        PersonBase(position, texture, 9.5f){
    this->playerHandler = playerHandler;
	this->gameControl = gameControl;
}
Player::~Player(){
}

void Player::init(){
    PersonBase::init();

    prevMovement.x = 0;
    prevMovement.y = 0;

	//Variables
	speed = 29;
	previousCoordinate.x = 0;
	previousCoordinate.y = 0;

    currentCoordinate = getCoordinate();
    wallsPlaced = true;

    sprPerson.setPosition(position);
}


void Player::update(float delta){
    PersonBase::update(delta);

	//Two phases
	//1. Movement
	//2. CollisionChecking
    sf::Keyboard keyboard;

	//Movement
	sf::Vector2f curMovement(0,0);

    bool moving = false;

	float deltaSpeed = speed * delta;

	if(keyboard.isKeyPressed(sf::Keyboard::A) && position.x > 0 + 6){
		curMovement.x -= deltaSpeed;
		moving = true;
	}
	if(keyboard.isKeyPressed(sf::Keyboard::D)  && position.x < 800 - 6){
		curMovement.x += deltaSpeed;
		moving = true;
	}
	if(keyboard.isKeyPressed(sf::Keyboard::W) && position.y > 0 + 6){
		curMovement.y -= deltaSpeed;
		moving = true;
	}
	if(keyboard.isKeyPressed(sf::Keyboard::S) && position.y < 600 - 6){
		curMovement.y += deltaSpeed;
		moving = true;
	}

    //Diaognal movement not faster
    if((curMovement.x != 0) ^ (curMovement.y != 0)){
        curMovement.x *= 1.4f;
        curMovement.y *= 1.4f;
    }

	position += curMovement;
	col->setPosition(position);

	//Collision wall
    std::vector<ColShape*> surWalls = gameControl->getSurWalls(currentCoordinate);

    int ventil = 0;
    while(collisionHandler(surWalls) && ventil < 2){
        ventil++;
    }

    //Collision friend
    std::vector<Friend*>* friends = gameControl->getFriends();

    bool atFriends = false;

    for(std::vector<Friend*>::iterator it = friends->begin(); it != friends->end(); ++it){
        ColCircle* aggroCircle = (*it)->getAggroCircle();

        if(Collision::isWithin(position, aggroCircle)){
            (*it)->setAtPlayer(true, position);
            atFriends = true;

            sf::Vector2f returnVector;

            if(Collision::doesCollide(col, (*it)->getCol(), &returnVector)){
                position += returnVector;
            }

            if(moving == false){
                //I should rewrite this whole update block,
                //this code orientates the player towards a friend if the player isn't moving.
                curMovement.x = aggroCircle->getPosition().x - position.x;
                curMovement.y = aggroCircle->getPosition().y - position.y;
            }

            playerHandler->addScore((*it)->getValue(), position);
           // std::cout << "Her" << std::endl;

        }else{
            (*it)->setAtPlayer(false, position);
        }
    }

    setPosition(position);

    if(!moving && !atFriends){
        curMovement = prevMovement;
    }
    calculateSprite(delta, &curMovement, moving);

    prevMovement = curMovement;

    //Collision enemy
	sf::Vector2f notUsedReturn;
	std::vector<Enemy*>* enemies = gameControl->getEnemies();
    std::vector<Enemy*>::iterator it = enemies->begin();

    while(it != enemies->end()){

        if(Collision::doesCollide((*it)->getCol(), col, &notUsedReturn )){
            delete (*it);
            it = enemies -> erase(it);
            if(playerHandler -> looseLife()){ //Returns true on dead
                std::cout << "DØØØØØØØØØD" << std::endl;
                gameControl -> death();
                return; //Exits update
            }
        }else{
            it++;
        }
    }

    //Check if player moves into a new coordinate, if player does, enemies has to find new path
    sf::Vector2i posNewCoordinate = getCoordinate();
    if(posNewCoordinate.x != currentCoordinate.x || posNewCoordinate.y != currentCoordinate.y){
        //Message enemies about new coordinate
        if(wallsPlaced || (previousCoordinate.x != posNewCoordinate.x || previousCoordinate.y != posNewCoordinate.y) ){
            //This check is to prevent jugling
            //In reality I think the real fix was adjusting the heuristic value in pathfinding from stpud to not so stupid
            gameControl -> enemiesFindNewPath();
            wallsPlaced = false;
        }
        previousCoordinate = currentCoordinate;
        currentCoordinate = posNewCoordinate;
    }
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
