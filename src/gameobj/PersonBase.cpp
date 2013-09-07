#include <inc/gameobj/PersonBase.h>
#include <inc/gameobj/GameControl.h>


PersonBase::PersonBase(sf::Vector2f position, sf::Texture* texture) : CENTER(8,12){
    this->position = position;
    this->texPerson = texture;
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
	animationSpeed = 6;
}


void PersonBase::render(sf::RenderWindow &window){
    window.draw(sprPerson);
}

void PersonBase::calculateSprite(float delta, sf::Vector2f* movement){
    if(movement->y != 0 || movement->x != 0){
        float newRotation = MathEssential::toDegrees(atan2(movement->y, movement->x));
        if(rotation != newRotation){
            rotation = newRotation;
            sprPerson.setRotation(rotation);
            col->setRotation(rotation);
        }

        //Animation
        time = (time + delta * animationSpeed);
        if(time >= 4){
            time -= 4;
        }
    }else{
        time = 0;
    }

    int frame = (int) time;

    sprPerson.setTextureRect(sf::IntRect(frame * 16,0,16,24));
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
