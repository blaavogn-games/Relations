#include <inc/gameobj/handler/PlayerHandler.h>
#include <inc/gameobj/GameControl.h>

PlayerHandler::PlayerHandler(GameControl* gameControl) : MAXLIVES(3){
    this -> gameControl = gameControl;
}

PlayerHandler::~PlayerHandler(){
    if(player){
        delete player;
    }
    if(scoreDisplay){
        delete scoreDisplay;
    }
    for(std::vector<sf::Sprite*>::iterator it = sprLives.begin(); it != sprLives.end(); ++it){
        delete *it;
    }
    sprLives.clear();
}

void PlayerHandler::init(){
	//Load data
    texLife.loadFromFile("res/img/player/life.png");
    texPlayer.loadFromFile("res/img/player/player.png");

    player = new Player(this, sf::Vector2f(160,280) , &texPlayer);
    player -> init();

    scoreDisplay = new ScoreDisplay();
	scoreDisplay -> init();

    lives = MAXLIVES;

    //SprLives init()
    const int STARTX = 760, STARTY = 10, HEARTSPACE = 22;

    for(int i = 0; i < MAXLIVES; i++){
        sf::Sprite* tempSprite = new sf::Sprite(texLife);
        tempSprite -> setPosition(STARTX - i * HEARTSPACE , STARTY);
        sprLives.push_back(tempSprite);
    }

}

void PlayerHandler::update(float delta){
    player      -> update(delta);
    scoreDisplay-> update(delta);
}

void PlayerHandler::render(sf::RenderWindow &window){
    player -> render(window);
    scoreDisplay -> render(window);

    //Displaying lives, should perhaps have own class
    for(std::vector<sf::Sprite*>::iterator it = sprLives.begin(); it != sprLives.end(); ++it){
        window.draw(**it);
    }
}

void PlayerHandler::addScore(float value){
    scoreDisplay -> addScore(value);
}

bool PlayerHandler::looseLife(){

    lives --;

    if(lives == 1){
        return true;
    }
    delete sprLives.back();
    sprLives.pop_back();
    return false;
}


sf::Vector2i PlayerHandler::getPlayerCoordinate(){
    return player -> getCoordinate();
}

//Connection line
std::vector<ColShape*> PlayerHandler::getSurWalls(sf::Vector2i coordinate){
    return gameControl -> getSurWalls(coordinate);
}

std::vector<Enemy*>* PlayerHandler::getEnemies(){
    return gameControl -> getEnemies();
}

std::vector<Friend*>* PlayerHandler::getFriends(){
    return gameControl -> getFriends();
}

void PlayerHandler::resetGame(){
    gameControl -> resetGame();
}

void PlayerHandler::enemiesFindNewPath(){
    gameControl -> enemiesFindNewPath();
}
