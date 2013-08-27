#include <inc/alarm/Alarm.h>

Alarm::Alarm(GameObj* owner){
    this->owner = owner;

}

Alarm::~Alarm(){
    for(std::vector<Timer*>::iterator it = timers.begin(); it != timers.end() ; ++it ){
        delete *it;
    }
    timers.clear();
}

//public
void Alarm::update(float delta){

    for(std::vector<Timer*>::iterator it = addBuffer.begin(); it != addBuffer.end(); ++it){
        timers.push_back((*it));
    }
    addBuffer.clear();

    std::vector<Timer*>::iterator it = timers.begin();
    while(it != timers.end()){
        (*it)->seconds -= delta;

        if((*it)->seconds < 0){
            owner->alarmAction((*it)->type);
            delete (*it);

            //The trick is that timers.erase returns an iterator to the proceeding vector element
            it = timers.erase(it);

        }else{
            ++it;
        }

    }
}

//public
void Alarm::addTimer(int type, int time){
    addBuffer.push_back(new Timer(type, time));
}
