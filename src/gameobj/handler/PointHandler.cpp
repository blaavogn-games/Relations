#include <inc/gameobj/handler/PointHandler.h>
#include <inc/gameobj/GameControl.h>

PointHandler::PointHandler(GameControl* gameControl){
    this->gameControl = gameControl;
}

PointHandler::~PointHandler(){
    for(std::vector<Point*>::iterator it = points.begin(); it != points.end(); ++it){
        delete *it;
    }
    points.clear();

    if(alarm){
        delete alarm;
    }
}

//public
void PointHandler::init(){


    texPoint.loadFromFile("res/img/point.png");

    alarm = new Alarm(this);
    alarm->addTimer(0, 1);

}

void PointHandler::update(float delta){

    for(std::vector<Point*>::iterator it = points.begin(); it != points.end(); ++it){
        (*it)->update(delta);
    }

    alarm->update(delta);
}

void PointHandler::render(sf::RenderWindow &window){
    for(std::vector<Point*>::iterator it = points.begin(); it != points.end(); ++it){
        (*it)->render(window);
    }
}

void PointHandler::alarmAction(int type){
    //Currently only 0
    addPoint();
    alarm->addTimer(0,12);
}

void PointHandler::addPoint(){

    sf::Vector2i coordinate;
    coordinate.x = rand() % GameControl::GRIDX; //Might need a seed, but it doesn't seem like it
    coordinate.y = rand() % GameControl::GRIDY;

    while(gameControl->getGrid(&coordinate) -> isWall()){
        coordinate.x = rand() % GameControl::GRIDX; //Might need a seed, but it doesn't seem like it
        coordinate.y = rand() % GameControl::GRIDY;
    }

    Point* tempPoint = new Point();
    tempPoint->init(&texPoint, coordinate);
    points.push_back(tempPoint);
}
