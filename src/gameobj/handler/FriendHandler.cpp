#include <inc/gameobj/handler/FriendHandler.h>
#include <inc/gameobj/GameControl.h>

FriendHandler::FriendHandler(GameControl* gameControl){
    this->gameControl = gameControl;
}

FriendHandler::~FriendHandler(){
    for(std::vector<Friend*>::iterator it = friends.begin(); it != friends.end(); ++it){
        delete *it;
    }
    friends.clear();

    if(alarm){
        delete alarm;
    }
}

//public
void FriendHandler::init(){
    texFriend.loadFromFile("res/img/friends/0.png");
    texEnemy.loadFromFile("res/img/enemies/enemy.png");
    texStillF.loadFromFile("res/img/friends/0s.png");

    alarm = new Alarm(this);
    addFriend(sf::Vector2f(19 * 32 + 16,9 * 32 + 16));
}

void FriendHandler::update(float delta){

    for(std::vector<Friend*>::iterator it = friends.begin(); it != friends.end(); ++it){
        (*it)->update(delta);
    }

    alarm->update(delta);
}

void FriendHandler::render(sf::RenderWindow &window){
    for(std::vector<Friend*>::iterator it = friends.begin(); it != friends.end(); ++it){
        (*it)->render(window);
    }
}

void FriendHandler::alarmAction(int type){
    //Currently only 0
    addFriend();
}

void FriendHandler::addFriend(){

    sf::Vector2i coordinate;
    coordinate.x = rand() % GameControl::GRIDX; //Might need a seed, but it doesn't seem like it
    coordinate.y = rand() % GameControl::GRIDY;

    while(gameControl->getGrid(&coordinate) -> isWall()){
        coordinate.x = rand() % GameControl::GRIDX;
        coordinate.y = rand() % GameControl::GRIDY;
    }
    addFriend(sf::Vector2f(coordinate.x * GameControl::GRIDSIZE + 16, coordinate.y * GameControl::GRIDSIZE + 16));

}

void FriendHandler::addFriend(sf::Vector2f position){

    Friend* tempFriend = new Friend(this, position, &texFriend);
    tempFriend->init(&texEnemy, &texStillF);
    friends.push_back(tempFriend);

    alarm->addTimer(0,40);
}

bool FriendHandler::isWall(int x, int y){
    return gameControl->isWall(x, y);
}
