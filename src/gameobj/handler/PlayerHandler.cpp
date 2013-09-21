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
    texPlayer.loadFromFile("res/img/player/sheet.png");
    soundBufferLooseLife.loadFromFile("res/sound/looseLife.wav");

    soundLooseLife.setBuffer(soundBufferLooseLife);

    player = new Player(this, gameControl, sf::Vector2f(160,280) , &texPlayer);
    player -> init();

    scoreDisplay = new ScoreDisplay();
	scoreDisplay -> init();

    lives = MAXLIVES;

    for(int i = 0; i < MAXLIVES; i++){
        sf::Sprite* tempSprite = new sf::Sprite(texLife);
        tempSprite -> setPosition(760 - i * 22 , 10);
        sprLives.push_back(tempSprite);
    }

}

void PlayerHandler::update(float delta){
    player      -> update(delta);
    scoreDisplay -> update(delta);
}

void PlayerHandler::render(sf::RenderWindow &window){
    player -> render(window);
    scoreDisplay -> render(window);

    //Displaying lives, should perhaps have own class
    for(std::vector<sf::Sprite*>::iterator it = sprLives.begin(); it != sprLives.end(); ++it){
        window.draw(**it);
    }
}

void PlayerHandler::reset(){
    delete player;
    player = new Player(this, gameControl, sf::Vector2f(160,280) , &texPlayer);
    player -> init();

    delete scoreDisplay;
    scoreDisplay = new ScoreDisplay();
	scoreDisplay -> init();

	lives = MAXLIVES;

    for(std::vector<sf::Sprite*>::iterator it = sprLives.begin(); it != sprLives.end(); ++it){
        delete (*it);
    }
    sprLives.clear();

    for(int i = 0; i < MAXLIVES; i++){
        sf::Sprite* tempSprite = new sf::Sprite(texLife);
        tempSprite -> setPosition(760 - i * 22, 10);
        sprLives.push_back(tempSprite);
    }
}

void PlayerHandler::addScore(float value, sf::Vector2f pos){
    scoreDisplay -> addScore(value, pos);
}

bool PlayerHandler::looseLife(){
    soundLooseLife.play();
    lives --;
    delete sprLives.back();
    sprLives.pop_back();

    if(lives == 0){
        return true;
    }
    return false;
}

void PlayerHandler::death(){
    scoreDisplay->death();
}

sf::Vector2i PlayerHandler::getPlayerCoordinate(){
    return player -> getCoordinate();
}

void PlayerHandler::wallAdded(){
    player -> wallsPlaced = true;
}
