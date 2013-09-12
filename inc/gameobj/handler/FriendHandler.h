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
        GameControl* gameControl;
        Alarm* alarm;
        sf::Texture texFriend, texEnemy, texStillF;
        std::vector<Friend*> friends;

    public:
        FriendHandler(GameControl* gameControl);
        ~FriendHandler();

        void init();
        void update(float delta);
        void render(sf::RenderWindow &window);

        void addFriend();
        void addFriend(sf::Vector2f);

        void alarmAction(int);
        std::vector<Friend*>* getFriends(){ return &friends;}

        //pipeline
        bool isWall(int x, int y);

};


#endif
