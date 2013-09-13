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

    std::vector<sf::Vector2f>::iterator transformIt = transformBuffer.begin();
    while(transformIt != transformBuffer.end()){
        sf::Vector2f friendPosition = (*transformIt);

        //Finds friend at position, deletes friend and asks gameControl to add an enemy at position
        for(std::vector<Friend*>::iterator friendIt = friends.begin(); friendIt != friends.end(); ++friendIt){
            sf::Vector2f itPos = (*friendIt) -> getPosition();

            if(itPos.x == friendPosition.x && itPos.y == friendPosition.y){
                delete (*friendIt);
                friends.erase(friendIt);
                gameControl->addEnemy(itPos);
                break;
            }
        }

        transformIt = transformBuffer.erase(transformIt);
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

    alarm->addTimer(0,20);
}

void FriendHandler::newTarget(sf::Vector2i coordinate){
    //Every friend with coordinate == targetCoord finds new action
    for(std::vector<Friend*>::iterator it = friends.begin(); it != friends.end(); ++it){
        sf::Vector2i targetCoord = (*it) -> getTargetCoord();
        if(targetCoord.x == coordinate.x && targetCoord.y == coordinate.y){
            (*it)->newAction();
        }
    }
}

void FriendHandler::transform(sf::Vector2f position){
    transformBuffer.push_back(position);
}

bool FriendHandler::isWall(int x, int y){
    return gameControl->isWall(x, y);
}
