#ifndef POINT_H
#define POINT_H

#include <inc/gameobj/PersonBase.h>
#include <inc/col/ColCircle.h>
#include <inc/alarm/Alarm.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class FriendHandler;

class Friend : public PersonBase{
    private:
        FriendHandler* friendHandler;
        float blinkTime, blinkDefault;

        Alarm* alarm;
        sf::Texture *texEnemy; //A bit unlogical, texFriend is placed in the baseClass and is called texPerson
        sf::Vector2f target, movement;
        sf::Vector2i coordinate;
        sf::Sound soundBlink;
        bool moving, atPlayer, active;
        ColCircle *aggroCircle;

        int value;
        const float SPEED;

        void startBlink();
        void changeSprite(bool);
        void newTarget(); //Possible action
        void newRotation(); //Possible action

    public:
        Friend(FriendHandler*, sf::Vector2f, sf::Texture*, sf::SoundBuffer*);
        ~Friend();

        void init(sf::Texture*);
        void update(float delta);

        float getValue();

        void newAction();
        void alarmAction(int);
        void setAtPlayer(bool, sf::Vector2f);
        sf::Vector2i getTargetCoord();

        ColCircle* getAggroCircle(){ return aggroCircle; }
};

#endif
