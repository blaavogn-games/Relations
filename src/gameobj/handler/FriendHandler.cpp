#include <inc/gameobj/handler/FriendHandler.h>
#include <inc/gameobj/GameControl.h>

FriendHandler::FriendHandler(GameControl* gameControl) : spawnTime(20){
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

    for(int i = 0; i < FRIEND_TYPES; i++){
        texFriend[i].loadFromFile("res/img/friends/"+std::to_string(i)+".png");
    }

    texEnemy.loadFromFile("res/img/enemies/enemy.png");

    soundBufferBlink.loadFromFile("res/sound/blink.wav");
    soundBufferTrans.loadFromFile("res/sound/transform.wav");

    soundTrans.setBuffer(soundBufferTrans);

    alarm = new Alarm(this);
    addFriend(sf::Vector2f(12 * 32 + 16,9 * 32 + 16), 10);

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

void FriendHandler::reset(){
    for(std::vector<Friend*>::iterator it = friends.begin(); it != friends.end(); ++it){
        delete *it;
    }
    friends.clear();

    transformBuffer.clear();

    alarm->reset();

    addFriend(sf::Vector2f(12 * 32 + 16,9 * 32 + 16), 10);
}

void FriendHandler::alarmAction(int type){
    //Currently only 0
    addFriend();
}

void FriendHandler::addFriend(){

    sf::Vector2i coordinate;
    coordinate.x = rand() % GameControl::GRIDX; //Might need a seed, but it doesn't seem like it
    coordinate.y = rand() % GameControl::GRIDY;

    while(gameControl->getGrid(&coordinate) -> isWall() ||
          gameControl->getPath(coordinate).size() < 15){
        coordinate.x = rand() % GameControl::GRIDX;
        coordinate.y = rand() % GameControl::GRIDY;
    }
    addFriend(sf::Vector2f(coordinate.x * GameControl::GRIDSIZE + 16, coordinate.y * GameControl::GRIDSIZE + 16), spawnTime);
}

void FriendHandler::addFriend(sf::Vector2f position, float time){
    int iTex = rand() % FRIEND_TYPES;
    Friend* tempFriend = new Friend(this, position, &texFriend[iTex], &soundBufferBlink);
    tempFriend->init(&texEnemy);
    friends.push_back(tempFriend);

    alarm->addTimer(0,time);
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
    soundTrans.play();
    transformBuffer.push_back(position);
}

bool FriendHandler::isWall(int x, int y){
    return gameControl->isWall(x, y);
}
