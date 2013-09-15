#ifndef POINTHANDLER_H
#define POINTHANDLER_H

#include <inc/alarm/Alarm.h>
#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/Friend.h>

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <vector>

//Forward dec
class GameControl;

class FriendHandler : public GameObj{
    private:
        enum {FRIEND_TYPES = 6};

        GameControl* gameControl;
        Alarm* alarm;
        sf::Texture texEnemy;
        sf::Texture texFriend[FRIEND_TYPES];
        std::vector<Friend*> friends;
        std::vector<sf::Vector2f> transformBuffer;

        const float spawnTime;

    public:
        FriendHandler(GameControl* gameControl);
        ~FriendHandler();

        void init();
        void update(float delta);
        void render(sf::RenderWindow &window);
        void reset();

        void addFriend();
        void addFriend(sf::Vector2f, float);
        void transform(sf::Vector2f);
        void newTarget(sf::Vector2i);

        void alarmAction(int);
        std::vector<Friend*>* getFriends(){ return &friends;}

        //pipeline
        bool isWall(int x, int y);

};


#endif
