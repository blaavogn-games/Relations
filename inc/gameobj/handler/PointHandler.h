#ifndef POINTHANDLER_H
#define POINTHANDLER_H

#include <inc/alarm/Alarm.h>
#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/Point.h>

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <vector>

//Forward dec
class GameControl;

class PointHandler : public GameObj{
    private:
        GameControl* gameControl;
        Alarm* alarm;
        sf::Texture texPoint;
        std::vector<Point*> points;

    public:
        PointHandler(GameControl* gameControl);
        ~PointHandler();

        void init();
        void update(float delta);
        void render(sf::RenderWindow &window);

        void addPoint();
        void alarmAction(int);
        std::vector<Point*>* getPoints(){ return &points;}

};


#endif
