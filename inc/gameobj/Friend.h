#ifndef POINT_H
#define POINT_H

#include <inc/gameobj/PersonBase.h>
#include <inc/col/ColCircle.h>
#include <inc/alarm/Alarm.h>

#include <SFML/Graphics.hpp>

class FriendHandler;

class Friend : public PersonBase{
    private:
        FriendHandler* friendHandler;
        float value, blinkTime, blinkDefault;
        Alarm* alarm;
        sf::Texture* texEnemy;
        sf::Vector2f target, movement;
        sf::Vector2i coordinate;
        bool moving;

        const float SPEED;

        void alarmReset();
        void setEnemy();
        void setFriend();
        void findTarget();

    public:
        Friend(FriendHandler*, sf::Vector2f, sf::Texture*, sf::Texture*);
        ~Friend();

        void init();
        void update(float delta);

        void alarmAction(int);

        float getValue();
};



#endif
