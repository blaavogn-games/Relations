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
    texControls.loadFromFile("res/img/menu/controls.png");
    texCredits.loadFromFile("res/img/menu/credits.png");

    sprTitle.setTexture(texTitle);
    sprTitle.setOrigin(sprTitle.getGlobalBounds().width / 2 , sprTitle.getGlobalBounds().height / 2);
    sprTitle.setPosition(400,100);

    sprInfo.setTexture(texControls);
    sprInfo.setPosition(440,280);

    const int POSX = 100, POSY = 220, SPACEY = 66;

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
    window.clear(sf::Color(185,250,185,255));
    window.draw(sprTitle);
    window.draw(sprInfo);

    for(std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it){
        (*it)->render(window);
    }

}

void MenuControl::action(int type){
    switch(type){
        case 0: //Play
            programControl->startGame();
        break;
        case 1: //Controls
            sprInfo.setTexture(texControls);
        break;
        case 2: //Credits
            sprInfo.setTexture(texCredits);
        break;
        case 3: //Quit
            programControl->close();
        break;
    }
}
