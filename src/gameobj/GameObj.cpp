#include <inc/gameobj/GameObj.h>

#include <iostream>


//These functions is currently going to be overridden 100% of the time
//Might be a good idea to enable a basic show sprite gameObj
void GameObj::init(){}
void GameObj::update(float delta){}
void GameObj::render(sf::RenderWindow &window){}

//Alarm action should run a switch on type and call corresponding function
//e.g. On player 0 = reload over, 1 = wall cooldown over, 2 = loose hp etc...
void GameObj::alarmAction(int type){}
