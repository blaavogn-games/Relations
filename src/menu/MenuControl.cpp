#include <inc/menu/MenuControl.h>
#include <inc/gameobj/ProgramControl.h>

#include <iostream>

MenuControl::MenuControl(ProgramControl *programControl){
    this->programControl = programControl;
}

MenuControl::~MenuControl(){

}

void MenuControl::init(){

    state = MAIN_MENU;

    texTitle.loadFromFile("res/img/menu/title.png");
    sprTitle.setTexture(texTitle);
    sprTitle.setOrigin(sprTitle.getGlobalBounds().width / 2 , sprTitle.getGlobalBounds().height / 2);
    sprTitle.setPosition(400,80);

    const int POSX = 50, POSY = 220, SPACEY = 52;

    for(int i = 0; i < 4; i++){
        Button* tempButton = new Button(this);
        tempButton->init(i, sf::Vector2f(POSX, POSY + SPACEY * i));
        buttons.push_back(tempButton);
    }
}

void MenuControl::update(float delta, sf::Vector2i &mousePosition){
    for(std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it){
        (*it)->update(mousePosition);
    }

}

void MenuControl::render(sf::RenderWindow &window){
    window.clear(sf::Color(30,255,30,255));
    window.draw(sprTitle);

    for(std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it){
        (*it)->render(window);
    }

}

void MenuControl::action(int type){
    std::cout << type << std::endl;
    switch(type){
        case 0:

        break;
        case 1:

        break;

        case 2:

        break;
        case 3:
            programControl->close();
        break;
    }
}
