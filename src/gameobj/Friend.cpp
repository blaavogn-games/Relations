#include <inc/gameobj/Friend.h>
#include <inc/gameobj/handler/FriendHandler.h>
#include <inc/gameobj/GameControl.h>
#include <inc/col/math/MathVector.h>

Friend::Friend(FriendHandler* friendHandler, sf::Vector2f position , sf::Texture* texFriend, sf::SoundBuffer* soundBuffTrans)
        : PersonBase(position, texFriend, 8) , SPEED(10){
    this->friendHandler = friendHandler;
    soundBlink.setBuffer(*soundBuffTrans);
    soundBlink.setVolume(80);
}

Friend::~Friend(){
    if(alarm){
        delete alarm;
    }
    if(aggroCircle){
        delete aggroCircle;
    }
}

void Friend::init(sf::Texture* texEnemy){
    this->texEnemy = texEnemy;
    PersonBase::init();

    atPlayer = false;
    active = true;

    blinkDefault = 4.5;
    value = 15;

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
        case 0: //Changes sprite to enemy
            changeSprite(false);
            alarm->addTimer(1, .2f);
            soundBlink.play();
        break;
        case 1: //Set Friend //Should possibly be a function call
            changeSprite(true);
            blinkTime *= 0.81f;
            alarm->addTimer(0, blinkTime);
            if(blinkTime < 0.04f){
                friendHandler->transform(position);
            }
        break;
        case 2:
            newAction();
        break;
        case 3:
            active = true;
            sprPerson.setColor(sf::Color(255,255,255,255));
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

}

void Friend::newRotation(){
    movement.x = (rand() % 5) - 2;
    movement.y = (rand() % 5) - 2;

    float time = ((rand() % 4) / 4) + 1;

    alarm -> addTimer(2 , time);

    moving = false;
}

void Friend::changeSprite(bool friendSprite){
    if(friendSprite){
        sprPerson.setTexture(*texPerson);
    }else{
        sprPerson.setTexture(*texEnemy);
    }
}

void Friend::setAtPlayer(bool newAtPlayer, sf::Vector2f playerPos){
    if(atPlayer != newAtPlayer){
        if(newAtPlayer){
            alarm->deleteTimer(0);
            alarm->deleteTimer(1);
            alarm->deleteTimer(2);
            changeSprite(true);
        }else{
            startBlink();
            newAction();
        }
        atPlayer = newAtPlayer;

    }else if(atPlayer){
        moving = false;
        movement.x = playerPos.x - position.x;
        movement.y = playerPos.y - position.y;
    }
}


float Friend::getValue(){
    if(active){
        sprPerson.setColor(sf::Color(255,255,255,175));
        alarm->addTimer(3, 10);
        active = false;
        return value;
    }
    return 0;
}

sf::Vector2i Friend::getTargetCoord(){
    int tX = (int) target.x;
    int tY = (int) target.y;

    return sf::Vector2i((tX - tX % GameControl::GRIDSIZE) / GameControl::GRIDSIZE,
                        (tY - tY % GameControl::GRIDSIZE) / GameControl::GRIDSIZE);
}
