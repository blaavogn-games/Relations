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
        sf::Texture *texEnemy, *texStillF; //A bit unlogical, texFriend is placed in the baseClass and is called texPerson
        sf::Vector2f target, movement;
        sf::Vector2i coordinate;
        bool friendSprite, moving;

        const float SPEED;

        void alarmReset();
        void updateSprite();
        void newAction();
        void newTarget(); //Possible action
        void newRotation(); //Possible action

    public:
        Friend(FriendHandler*, sf::Vector2f, sf::Texture*);
        ~Friend();

        void init(sf::Texture*, sf::Texture*);
        void update(float delta);

        void alarmAction(int);

        float getValue();
};



#endif
