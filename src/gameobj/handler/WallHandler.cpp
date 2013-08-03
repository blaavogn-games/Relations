#include <inc/gameobj/handler/WallHandler.h>

#include <inc/gameobj/GameControl.h>
#include <iostream>

//private
void WallHandler::addWall(sf::Vector2i position){
    sf::Vector2i mapPos(position.x / GameControl::GRIDSIZE, position.y / GameControl::GRIDSIZE);

    //Is mouse coordinates within the window
    if(1 <= mapPos.x && mapPos.x < GameControl::GRIDX - 1 && 1 <= mapPos.y &&  mapPos.y < GameControl::GRIDY - 1 && !walls.count(mapPos) ){

        Wall* tempWall = new Wall(sf::Vector2f(position.x, position.y));
        tempWall->init();
        std::pair<sf::Vector2i, Wall* > tempValuePair (mapPos , tempWall);
        walls.insert(tempValuePair);
    }


}

sf::Vector2i WallHandler::getGridPosition(int posx, int posy){
    sf::Vector2i returnVector;
    returnVector.x = posx - (posx % GameControl::GRIDSIZE);
    returnVector.y = posy - (posy % GameControl::GRIDSIZE);
    return returnVector;
}

//Public
WallHandler::WallHandler(){

}

WallHandler::~WallHandler(){
    for(WallMap::iterator it = walls.begin(); it != walls.end(); ++it){
        delete it->second;
    }
	walls.clear();

}

void WallHandler::init(){

	if (!txHighlight.loadFromFile("res/img/highlight.png"))
	{
		//std::cout << "Error while loading player texture" << std::endl;
	}
	sprHighlight.setTexture(txHighlight);

}


void WallHandler::update(float delta, sf::Event &event, sf::Vector2i &mousePosition){
    //Handles highlight and mouse position
    sf::Vector2i mouseGridPosition = getGridPosition(mousePosition.x , mousePosition.y);
    sprHighlight.setPosition(sf::Vector2f(mouseGridPosition.x,mouseGridPosition.y));

    sf::Mouse mouse;
    if(mouse.isButtonPressed(sf::Mouse::Left)){
        addWall(mouseGridPosition);
    }

    sf::Keyboard key;
    if(key.isKeyPressed(sf::Keyboard::Space)){
        pathfinder.findPath(sf::Vector2i(0,0) , sf::Vector2i(10,10));
    }
}

void WallHandler::render(sf::RenderWindow &window){
    window.draw(sprHighlight);
    for(WallMap::iterator it = walls.begin(); it != walls.end(); ++it){

        it->second->render(window);
    }
}


std::vector<Wall*> WallHandler::getSurWalls(sf::Vector2f &position){
    std::vector<Wall*> surWalls;

    sf::Vector2i gridPosition = getGridPosition((int) position.x , (int)position.y);
    sf::Vector2i mapPosition(gridPosition.x / GameControl::GRIDSIZE, gridPosition.y / GameControl::GRIDSIZE);

    //Get the 2x2 grid expanding from grid pos
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            sf::Vector2i tempKey(mapPosition.x + i, mapPosition.y + j);
            if(walls.count(tempKey)){
                surWalls.push_back(walls.at(tempKey));
            }
        }
    }

    return surWalls;
}
