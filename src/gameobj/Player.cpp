#include <inc/gameobj/Player.h>
#include <inc/gameobj/GameControl.h>

#include <iostream>

Player::Player(GameControl* gameControl) : CENTER(8 , 12) , MAXLIVES(3){
	this->gameControl = gameControl;
}
Player::~Player(){
	if(col){
        delete col;
	}
    if(scoreDisplay){
        delete scoreDisplay;
    }
}

void Player::init(){
	//Variables
	speed = 22;
    previousCoordinate = getCoordinate();

	//Player at 9,9 just for enemy testing
	position.x = 32 * 0 + 9;
	position.y = 32 * 0 + 9;

	//Dynamic vars
	col = new ColShape(position, sf::Vector2f(0,0));
	col->addCorner(sf::Vector2f(0 , -CENTER.y));
	col->addCorner(sf::Vector2f(CENTER.x , 0));
	col->addCorner(sf::Vector2f(0 , CENTER.y));
	col->addCorner(sf::Vector2f(-CENTER.x , 0));
	col->init();

	scoreDisplay = new ScoreDisplay();
	scoreDisplay->init();

	//Load data
	texPlayer.loadFromFile("res/img/player/player.png");
    texLife.loadFromFile("res/img/player/life.png");

    const int STARTX = 760, STARTY = 10, HEARTSPACE = 22;

    for(int i = 0; i < MAXLIVES; i++){
        sf::Sprite* tempSprite = new sf::Sprite(texLife);
        tempSprite -> setPosition(STARTX - i * HEARTSPACE , STARTY);
        lives.push_back(tempSprite);
    }

	sprPlayer.setTexture(texPlayer);
	sprPlayer.setOrigin(CENTER);
}


void Player::update(float delta){
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

    setRotation(curMovement);

	//Collision wall
    std::vector<ColShape*> surWalls = gameControl->getSurWalls(getPosition());

    int ventil = 0;
    while(collisionHandler(surWalls) && ventil < 1){
        ventil++;
    }

    sprPlayer.setPosition(position);

    //Collision friend
    std::vector<Friend*>* friends = gameControl->getFriends();
    std::vector<Friend*>::iterator friendsIt = friends->begin();

    sf::Vector2f notUsedReturn;

    while(friendsIt != friends->end()){
        if(Collision::doesCollide((*friendsIt)->getCol() , col , &notUsedReturn)){
            scoreDisplay->addScore((*friendsIt)->getValue());
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

        if(Collision::doesCollide((*it)->getColCircle(), col, &notUsedReturn )){
            delete (*it);
            it = enemies -> erase(it);
            if(looseLife()){ //Returns true on dead
                std::cout << "DØØØØØØØØØD" << std::endl;
                gameControl -> resetGame();
                return;
            }
        }else{
            it++;
        }

    }

    //Check if player moves into a new coordinate, if player does, enemies has to find new path
    sf::Vector2i currentCoordinate = getCoordinate();
    if(currentCoordinate.x != previousCoordinate.x || currentCoordinate.y != previousCoordinate.y){
        //Message enemies about new coordinate
        gameControl->enemiesFindNewPath();
    }
    previousCoordinate = currentCoordinate;

    scoreDisplay->update(delta);

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

void Player::render(sf::RenderWindow &window){
	window.draw(sprPlayer);
  //  col->render(window);
    for(std::vector<sf::Sprite*>::iterator it = lives.begin(); it != lives.end(); ++it){
        window.draw(**it);
    }

    scoreDisplay->render(window);
}

bool Player::looseLife(){

    if(lives.size() == 1){
        return true;
    }
    delete lives.back();
    lives.pop_back();
    return false;
}

ColShape* Player::getCol(){
    return col;
}

void Player::setRotation(sf::Vector2f curMovement){
    if(curMovement.y != 0 || curMovement.x != 0){
        float newRotation = MathEssential::toDegrees(atan2(curMovement.y, curMovement.x));
        if(newRotation != rotation){
            rotation = newRotation;
            sprPlayer.setRotation(rotation);
            col->setRotation(rotation);
        }
    }
}

sf::Vector2i Player::getPosition(){
    return sf::Vector2i( (int) position.x, (int) position.y);
}

sf::Vector2i Player::getCoordinate(){
    //center position
    int cX = (int)position.x, cY = (int)position.y;

    return sf::Vector2i( (int) ((cX - cX % GameControl::GRIDSIZE) / GameControl::GRIDSIZE),
                         (int) ((cY - cY % GameControl::GRIDSIZE) / GameControl::GRIDSIZE));
}
