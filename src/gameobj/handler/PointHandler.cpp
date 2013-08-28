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
}

//public
void PointHandler::init(){
    texPoint.loadFromFile("res/img/point.png");

    Point* tempPoint = new Point();
    tempPoint->init(&texPoint, sf::Vector2f(300,200));
    points.push_back(tempPoint);
}

void PointHandler::update(float delta){

    for(std::vector<Point*>::iterator it = points.begin(); it != points.end(); ++it){
        (*it)->update(delta);
    }
}

void PointHandler::render(sf::RenderWindow &window){
    for(std::vector<Point*>::iterator it = points.begin(); it != points.end(); ++it){
        (*it)->render(window);
    }
}
