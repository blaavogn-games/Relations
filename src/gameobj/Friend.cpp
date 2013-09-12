#include <inc/gameobj/Friend.h>
#include <inc/gameobj/handler/FriendHandler.h>
#include <inc/col/math/MathVector.h>
#include <inc/gameobj/GameControl.h>

Friend::Friend(FriendHandler* friendHandler, sf::Vector2f position , sf::Texture* texFriend)
        : PersonBase(position, texFriend) , SPEED(10){
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

    blinkDefault = 3;
    PersonBase::init();

	alarm = new Alarm(this);
    startBlink();
    newAction();

    aggroCircle = new ColCircle(&position, 15);
}

void Friend::update(float delta){
    if(moving){
        position += MathVector::scale(movement, delta);
        if(std::fabs(target.x - position.x) + std::fabs(target.y - position.y) < 0.3f){
            newAction();
        }
    }

    setPosition(sf::Vector2f(position.x, position.y));

    calculateSprite(delta, &movement);
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
            alarm->addTimer(1, .15f);
        break;
        case 1: //Should possibly be a function call
            friendSprite = true;
            updateSprite(); //Set Friend
            blinkTime *= 0.85f;
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

void Friend::setAtPlayer(bool newAtPlayer){
    if(atPlayer != newAtPlayer){
        if(newAtPlayer){
            alarm->deleteTimer(0);
            alarm->deleteTimer(1);
            friendSprite = true;
            updateSprite();
            std::cout << "deleteTimer" << std::endl;
        }else{
            startBlink();
            std::cout << "startBlinking" << std::endl;
        }

        atPlayer = newAtPlayer;
    }
}
