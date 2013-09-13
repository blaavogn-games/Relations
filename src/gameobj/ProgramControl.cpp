#include <inc/gameobj/ProgramControl.h>

ProgramControl::ProgramControl(){

}

ProgramControl::~ProgramControl(){
    if(gameControl){
        delete gameControl;
    }
    if(menuControl){
        delete menuControl;
    }
}

void ProgramControl::init(){
    closeWindow = false;

    menuControl = new MenuControl(this);
    menuControl -> init();

    gameControl = new GameControl();
    gameControl -> init();

    state = MENU_STATE;
}

void ProgramControl::update(float delta, sf::Vector2i mousePosition){
    switch(state){
        case MENU_STATE:
            menuControl -> update(delta, mousePosition);
        break;
        case GAME_STATE:
            gameControl -> update(delta, mousePosition);
        break;
    }
}

void ProgramControl::render(sf::RenderWindow &window){
    switch(state){
        case MENU_STATE:
            menuControl -> render(window);
        break;
        case GAME_STATE:
            gameControl -> render(window);
        break;
    }
    if(closeWindow){
        window.close();
    }
}

void ProgramControl::close(){
    closeWindow = true;
}
