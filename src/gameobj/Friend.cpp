#include <inc/gameobj/Friend.h>
#include <inc/gameobj/handler/FriendHandler.h>
#include <inc/col/math/MathVector.h>
#include <inc/gameobj/GameControl.h>

Friend::Friend(FriendHandler* friendHandler, sf::Vector2f position , sf::Texture* texFriend, sf::Texture* texEnemy)
        : PersonBase(position, texFriend) , SPEED(10){
    this->friendHandler = friendHandler;
    this->texEnemy = texEnemy;
}

Friend::~Friend(){
    if(alarm){
        delete alarm;
    }
}

void Friend::init(){
    blinkDefault = 5;
    PersonBase::init();
    value = 20;
	coordinate = getCoordinate();

	alarm = new Alarm(this);
	alarmReset();

    findTarget();
}

void Friend::update(float delta){
    if(moving){
        position += MathVector::scale(movement, delta);
    }
    setPosition(position);

    calculateSprite(delta, &movement);
    alarm->update(delta);
}

void Friend::alarmReset(){
    blinkTime = blinkDefault;
    alarm->reset();
    alarm->addTimer(0, blinkTime);
}

void Friend::alarmAction(int type){
    switch(type){
        case 0:
            setEnemy();
        break;
        case 1:
            setFriend();
        break;
    }
}

void Friend::findTarget(){

    std::vector<sf::Vector2i> posTargets;
    if(! friendHandler->isWall(coordinate.x, coordinate.y - 1)){ //top
        posTargets.push_back(sf::Vector2i(coordinate.x, coordinate.y - 1));
    }
    if(! friendHandler->isWall(coordinate.x, coordinate.y + 1)){ //bot
        posTargets.push_back(sf::Vector2i(coordinate.x, coordinate.y + 1));
    }
    if(! friendHandler->isWall(coordinate.x - 1, coordinate.y)){ //left
        posTargets.push_back(sf::Vector2i(coordinate.x - 1, coordinate.y));
    }
    if(! friendHandler->isWall(coordinate.x, coordinate.y + 1)){ //right
        posTargets.push_back(sf::Vector2i(coordinate.x + 1, coordinate.y));
    }
    int newTarget = rand() % posTargets.size();

    target.x = posTargets.at(newTarget).x * GameControl::GRIDSIZE;
    target.y = posTargets.at(newTarget).y * GameControl::GRIDSIZE;

    sf::Vector2f tempMovement;
    tempMovement.x = target.x - position.x;
    tempMovement.y = target.y - position.y;

    movement = MathVector::scale( MathVector::normalize(tempMovement) , SPEED);

    moving = true;
}

void Friend::setEnemy(){
    sprPerson.setTexture(*texEnemy);
    alarm->addTimer(1, .12f);
}

void Friend::setFriend(){
    sprPerson.setTexture(*texPerson);
    blinkTime *= 0.7f;
    alarm->addTimer(0, blinkTime);
}

float Friend::getValue(){
    return value;
}
