#include <inc/gameobj/Player.h>
#include <inc/gameobj/GameControl.h>

#include <iostream>

Player::Player(GameControl* gameControl) : RADIUS(8) , MAXLIVES(9){
	this->gameControl = gameControl;
}
Player::~Player(){
	if(colCircle){
        delete colCircle;
	}
    if(scoreDisplay){
        delete scoreDisplay;
    }
}

void Player::init(){
	//Variables
	speed = 33;
    previousCoordinate = getCoordinate();

	//Player at 9,9 just for enemy testing
	position.x = 32 * 9 + 9;
	position.y = 32 * 9 + 9;

	//Dynamic vars
	colCircle = new ColCircle(position, RADIUS);

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
}


void Player::update(float delta){
	//Two phases
	//1. Movement
	//2. CollisionChecking

    sf::Keyboard keyboard;

	//Movement
	sf::Vector2f curMovement;

	float deltaSpeed = speed * delta;

	if(keyboard.isKeyPressed(sf::Keyboard::A) && position.x > 0){
		curMovement.x -= deltaSpeed;
	}
	if(keyboard.isKeyPressed(sf::Keyboard::D)  && position.x < 784){
		curMovement.x += deltaSpeed;
	}

	if(keyboard.isKeyPressed(sf::Keyboard::W) && position.y > 0 ){
		curMovement.y -= deltaSpeed;
	}
	if(keyboard.isKeyPressed(sf::Keyboard::S) && position.y < 584){
		curMovement.y += deltaSpeed;
	}

	position += curMovement;
	colCircle->setPosition(position);

	//Collision wall
    std::vector<ColShape*> surWalls = gameControl->getSurWalls(getPosition());

    int ventil = 0;
    while(collisionHandler(surWalls) && ventil < 10){
        ventil++;
    }

    sprPlayer.setPosition(position);

    //Collision points
    std::vector<Point*>* points = gameControl->getPoints();
    std::vector<Point*>::iterator pointsIt = points->begin();

    while(pointsIt != points->end()){
        if(Collision::doesCollide(*colCircle , (*pointsIt)->getColCircle())){
            scoreDisplay->addScore((*pointsIt)->getValue());
            delete (*pointsIt);
            pointsIt = points -> erase (pointsIt);
        }else{
            pointsIt++;
        }

    }

    //Collision enemy
	std::vector<Enemy*>* enemies = gameControl->getEnemies();
    std::vector<Enemy*>::iterator it = enemies->begin();

    while(it != enemies->end()){

        if(Collision::doesCollide(*colCircle,(*it)->getColCircle())){
            delete (*it);
            it = enemies -> erase(it);
            looseLife();
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
        if(Collision::doesCollide(colCircle, *it , &returnVector)){
            position -= returnVector;
            colCircle->setPosition(position);
            res = true;
        }
    }
    return res;
}

void Player::render(sf::RenderWindow &window){
	window.draw(sprPlayer);

    for(std::vector<sf::Sprite*>::iterator it = lives.begin(); it != lives.end(); ++it){
        window.draw(**it);
    }

    scoreDisplay->render(window);
}

void Player::looseLife(){

    if(lives.size() == 1){
        std::cout << "DØØØØØØØØØD" << std::endl;
    }

    delete lives.back();
    lives.pop_back();
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

