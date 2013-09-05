#include <inc/gameobj/Friend.h>
#include <inc/gameobj/GameControl.h>

Friend::Friend(sf::Vector2f position , sf::Texture* texture) : PersonBase(position, texture){
}

Friend::~Friend(){
    if(alarm){
        delete alarm;
    }
}

void Friend::init(){
    PersonBase::init();
    value = 20;
	alarm = new Alarm(this);
}

void Friend::update(float delta){
    setPosition(position);
}


void Friend::alarmAction(int type){

}

float Friend::getValue(){
    return value;
}


