#include <inc/menu/Button.h>
#include <inc/menu/MenuControl.h>

Button::Button(MenuControl *menuControl){
    this->menuControl = menuControl;
}

Button::~Button(){}

void Button::init(int type, sf::Vector2f position){
    this->type = type;

    hover = false;
    firstMousePress = true;

    texture.loadFromFile("res/img/menu/" + std::to_string(type) + ".png");

    sprite.setTexture(texture);
    width = sprite.getGlobalBounds().width;

    sprite.setTextureRect(sf::IntRect(0,0,width,40));
    sprite.setPosition(position);
}

void Button::update(sf::Vector2i &mousePosition){
    bool hoverNow = sprite.getGlobalBounds().contains(mousePosition.x,mousePosition.y);

    if(hoverNow && !hover){
        sprite.setTextureRect(sf::IntRect(0,40,width,40));
        hover = true;
    }else if(!hoverNow && hover){
        sprite.setTextureRect(sf::IntRect(0,0,width,40));
        hover = false;
    }

    sf::Mouse mouse;

    if(mouse.isButtonPressed(sf::Mouse::Left)){
        if(firstMousePress == true && hover){
            menuControl -> action(type);
            firstMousePress = false;
        }
    }else{
        firstMousePress = true;
    }
}

void Button::render(sf::RenderWindow &window){
    window.draw(sprite);
}

