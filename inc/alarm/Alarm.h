#ifndef ALARM_H
#define ALARM_H

#include <inc/alarm/Timer.h>
#include <inc/gameobj/GameObj.h>

#include <vector>

class Alarm{
    private:
        GameObj* owner;
        std::vector<Timer*> timers;
        std::vector<Timer*> addBuffer;

    public:
        Alarm(GameObj* owner);
        ~Alarm();
        void update(float delta);
        void addTimer(int , int);
};

#endif
