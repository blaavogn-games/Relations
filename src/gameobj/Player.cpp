#include <inc/gameobj/Player.h>
#include <inc/gameobj/GameControl.h>

#include <iostream>

Player::Player(GameControl* gameControl) : RADIUS(8){
	this->gameControl = gameControl;
}
Player::~Player(){
	if(colCircle)
		delete colCircle;
}

void Player::init(){
	//Variables
	speed = 80;
    previousCoordinate = getCoordinate();


	//Player at 9,9 just for enemy testing
	position.x = 32 * 9 + 9;
	position.y = 32 * 9 + 9;

	//Dynamic vars
	colCircle = new ColCircle(position, RADIUS);

	//Load data
	if (!texture.loadFromFile("res/img/player.png"))
	{
		//UNHANDLED ERROR
	}

	sprite.setTexture(texture);


}

void Player::update(float delta){
	//Two phases
	//1. Movement
	//2. CollisionChecking

    sf::Keyboard keyboard;

	//Movement
	sf::Vector2f curMovement;

	float deltaSpeed = speed * delta;

	if(keyboard.isKeyPressed(sf::Keyboard::A) ){
		curMovement.x -= deltaSpeed;
	}
	if(keyboard.isKeyPressed(sf::Keyboard::D) ){
		curMovement.x += deltaSpeed;
	}

	if(keyboard.isKeyPressed(sf::Keyboard::W) ){
		curMovement.y -= deltaSpeed;
	}
	if(keyboard.isKeyPressed(sf::Keyboard::S) ){
		curMovement.y += deltaSpeed;
	}

	position += curMovement;
	colCircle->setPosition(position);

	//Collision
    std::vector<ColShape*> surWalls = gameControl->getSurWalls(getPosition());

    int ventil = 0;
    while(collisionHandler(surWalls) && ventil < 10){
        ventil++;
    }

    sprite.setPosition(position);

	if(keyboard.isKeyPressed(sf::Keyboard::Space) ){
		std::vector<Enemy*>* enemies = gameControl->getEnemies();

		for(std::vector<Enemy*>::iterator it = enemies->begin(); it != enemies->end();++it){
			if(Collision::doesCollide(*colCircle,(*it)->getColCircle())){
				std::cout << "Yahooo" << std::endl;
			}
		}
	}

    //Check if player moves into a new coordinate, if player does, enemies has to find new path
    sf::Vector2i currentCoordinate = getCoordinate();
    if(currentCoordinate.x != previousCoordinate.x || currentCoordinate.y != previousCoordinate.y){
        //Message enemies about new coordinate
        gameControl->enemiesFindNewPath();
    }
    previousCoordinate = currentCoordinate;


}

bool Player::collisionHandler(std::vector<ColShape*> surWalls){
    bool res = false;
    for(std::vector<ColShape*>::iterator it = surWalls.begin(); it != surWalls.end(); it++){
        sf::Vector2f returnVector;
        if(Collision::doesCollide(colCircle, *it , &returnVector)){
            position -= returnVector;
            colCircle->setPosition(position);
            res = true;
        }
    }
    return res;
}

void Player::render(sf::RenderWindow &window){
	window.draw(sprite);
}

ColCircle* Player::getCol(){
    return colCircle;
}

sf::Vector2i Player::getPosition(){
    return sf::Vector2i( (int) position.x, (int) position.y);
}

sf::Vector2i Player::getCoordinate(){
    //center position
    int cX = (int)position.x + RADIUS, cY = (int)position.y + RADIUS;

    return sf::Vector2i( (int) ((cX - cX % GameControl::GRIDSIZE) / GameControl::GRIDSIZE),
                         (int) ((cY - cY % GameControl::GRIDSIZE) / GameControl::GRIDSIZE));
}
