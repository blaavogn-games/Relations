#ifndef TIMER_H
#define TIMER_H

#include <iostream>

class Timer{
    private:

    public:
        Timer(int type, float seconds);

        int type;
        float seconds;
};
#endif
