#include <inc/gameobj/Friend.h>
#include <inc/gameobj/handler/FriendHandler.h>
#include <inc/gameobj/GameControl.h>
#include <inc/col/math/MathVector.h>

Friend::Friend(FriendHandler* friendHandler, sf::Vector2f position , sf::Texture* texFriend)
        : PersonBase(position, texFriend, 4) , SPEED(10){
    this->friendHandler = friendHandler;
}

Friend::~Friend(){
    if(alarm){
        delete alarm;
    }
    if(aggroCircle){
        delete aggroCircle;
    }
}

void Friend::init(sf::Texture* texEnemy, sf::Texture* texStillF){
    this->texEnemy = texEnemy;
    this->texStillF = texStillF;

    friendSprite = true;
    atPlayer = false;

    //blinkDefault = 5;
    blinkDefault = 1;
    PersonBase::init();

	alarm = new Alarm(this);
    startBlink();
    newAction();

    aggroCircle = new ColCircle(&position, 50);
}

void Friend::update(float delta){
    if(moving){
        position += MathVector::scale(movement, delta);
        if(std::fabs(target.x - position.x) + std::fabs(target.y - position.y) < 0.3f){
            newAction();
        }
    }

    setPosition(sf::Vector2f(position.x, position.y));

    calculateSprite(delta, &movement, moving);
    alarm->update(delta);
}

void Friend::startBlink(){
    blinkTime = blinkDefault;
    alarm->addTimer(0, blinkTime);
}

void Friend::alarmAction(int type){
    switch(type){
        case 0:
            friendSprite = false;
            updateSprite(); //Set enemy
            alarm->addTimer(1, .2f);
        break;
        case 1: //Should possibly be a function call
            friendSprite = true;
            updateSprite(); //Set Friend
            blinkTime *= 0.81f;
            alarm->addTimer(0, blinkTime);
            if(blinkTime < 0.08f){
                friendHandler->transform(position);
            }
        break;
        case 2:
            newAction();
        break;
    }
}

void Friend::newAction(){
    int action = rand() % 4;

    if(action == 0){
        newTarget();
    }else{
        newRotation();
    }
}

void Friend::newTarget(){
	coordinate = getCoordinate();

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
    if(! friendHandler->isWall(coordinate.x + 1, coordinate.y)){ //right
        posTargets.push_back(sf::Vector2i(coordinate.x + 1, coordinate.y));
    }
    int newTarget = rand() % posTargets.size();
    target.x = posTargets.at(newTarget).x * GameControl::GRIDSIZE + 16;
    target.y = posTargets.at(newTarget).y * GameControl::GRIDSIZE + 16;

    sf::Vector2f tempMovement;
    tempMovement.x = target.x - position.x;
    tempMovement.y = target.y - position.y;

    movement = MathVector::scale( MathVector::normalize(tempMovement) , SPEED);

    moving = true;

    updateSprite();
}

void Friend::newRotation(){
    movement.x = (rand() % 5) - 2;
    movement.y = (rand() % 5) - 2;

    float time = ((rand() % 4) / 4) + 1;

    alarm -> addTimer(2 , time);

    moving = false;
    updateSprite();
}

void Friend::updateSprite(){
    if(friendSprite){
        if(moving){
            sprPerson.setTexture(*texPerson);
        }else{
            sprPerson.setTexture(*texStillF);
        }
    }else{
        sprPerson.setTexture(*texEnemy);
    }
}

void Friend::setAtPlayer(bool newAtPlayer, sf::Vector2f playerPos){
    if(atPlayer != newAtPlayer){
        if(newAtPlayer){
            alarm->reset();
            friendSprite = true;
            moving = false;
            updateSprite();
        }else{
            startBlink();
            newAction();
        }
        atPlayer = newAtPlayer;

    }else if(atPlayer){
        movement.x = playerPos.x - position.x;
        movement.y = playerPos.y - position.y;
    }
}

sf::Vector2i Friend::getTargetCoord(){
    int tX = (int) target.x;
    int tY = (int) target.y;

    return sf::Vector2i((tX - tX % GameControl::GRIDSIZE) / GameControl::GRIDSIZE,
                        (tY - tY % GameControl::GRIDSIZE) / GameControl::GRIDSIZE);
}
