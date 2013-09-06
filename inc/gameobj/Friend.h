#ifndef POINT_H
#define POINT_H

#include <inc/gameobj/PersonBase.h>
#include <inc/col/ColCircle.h>
#include <inc/alarm/Alarm.h>

#include <SFML/Graphics.hpp>

class Friend : public PersonBase{
    private:
        float value;


        Alarm* alarm;

    public:
        Friend(sf::Vector2f, sf::Texture*);
        ~Friend();

        void init();
        void update(float delta);

        void alarmAction(int);

        float getValue();
};



#endif
