#include <inc/gameobj/PersonBase.h>
#include <inc/gameobj/GameControl.h>


PersonBase::PersonBase(sf::Vector2f position, sf::Texture* texture, float animationSpeed) : CENTER(7,12){
    this->position = position;
    this->texPerson = texture;
    this->animationSpeed = animationSpeed;
}

PersonBase::~PersonBase(){
    if(col){
        delete col;
    }

} //Texture neeed to be deleted if it is not loaded by a handler

void PersonBase::init(){
    sprPerson.setTexture(*texPerson);
    sprPerson.setOrigin(CENTER);

    col = new ColShape(position, sf::Vector2f(0,0));
	col->addCorner(sf::Vector2f(0 , -CENTER.y));
	col->addCorner(sf::Vector2f(CENTER.x , 0));
	col->addCorner(sf::Vector2f(0 , CENTER.y));
	col->addCorner(sf::Vector2f(-CENTER.x , 0));
	col->init();

	time = 0;
}


void PersonBase::render(sf::RenderWindow &window){
    window.draw(sprPerson);
}

void PersonBase::calculateSprite(float delta, sf::Vector2f* movement, bool moving){

    float newRotation = MathEssential::toDegrees(atan2(movement->y, movement->x));

    if(rotation != newRotation){
        rotation = newRotation;
        sprPerson.setRotation(rotation);
        col->setRotation(rotation);
    }

    if(moving){
        //Animation
        time = (time + delta * animationSpeed);
        if(time >= 8){
            time -= 8;
        }
    }else{
        time = 0;
    }

    int frameX = (int) time % 4;
    int frameY = (int) time / 4;

    sprPerson.setTextureRect(sf::IntRect(frameX * 14, frameY * 24,14,24));
}

void PersonBase::setPosition(sf::Vector2f newPosition){
    sprPerson.setPosition(newPosition);
    col->setPosition(newPosition);
}

sf::Vector2i PersonBase::getCoordinate(){
    int pX = (int) position.x;
    int pY = (int) position.y;

    return sf::Vector2i( (int) ((pX - pX % GameControl::GRIDSIZE) / GameControl::GRIDSIZE),
                         (int) ((pY - pY % GameControl::GRIDSIZE) / GameControl::GRIDSIZE));
}
