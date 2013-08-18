#include <inc/gameobj/handler/GridHandler.h>
#include <inc/gameobj/GameControl.h>

#include <iostream>

//private
void GridHandler::attemptToAddWall(sf::Vector2i position){
    sf::Vector2i gridCoordinate(position.x / GameControl::GRIDSIZE, position.y / GameControl::GRIDSIZE);
    //Is mouse coordinates within the window
    if(1 <= gridCoordinate.x && gridCoordinate.x < GameControl::GRIDX - 1 && 1 <= gridCoordinate.y &&  gridCoordinate.y < GameControl::GRIDY - 1 && !walls.count(gridCoordinate) ){

        //In order for placing a wall following checks should be made
        //1. Get all enemies that has the wallPoint as a point in their path
        //1a.      if 0: Place wall

        //2. Does an alternative path exist for all of these enemies?
        //2a     false: don't place wall

        //3. Place wall and find make the alternative paths the new paths


        //1.
        std::vector<Enemy*> enemies = gameControl -> getEnemiesWithPathPoint(gridCoordinate);

        //1a
        if( enemies.size() == 0){
            addWall(gridCoordinate);
            return;
        }

        //Adding wall temporarily to do search
        pathfinder -> addWall(gridCoordinate);

        //2

        bool legalWall = true;
        std::vector<std::deque<sf::Vector2i>> tempPaths;

        for(unsigned int i = 0; i < enemies.size(); i++){

            std::deque<sf::Vector2i> tempPath = getPath( enemies.at(i)->getPosition(), gameControl -> getPlayerCoordinate());

            if(tempPath.size() != 0){
                tempPaths.push_back( tempPath);
            }else{
                //2a
                std::cout << "Not legal to place wall" << std::endl;
                pathfinder -> removeWall(gridCoordinate);
                legalWall = false;
                break;
            }
        }

        //3
        if(legalWall){
            for(unsigned int i = 0; i < enemies.size(); i++){
                enemies.at(i) -> setPath(tempPaths.at(i));
            }
            //Redundant to remove wall but necesarry atm
            pathfinder -> removeWall(gridCoordinate);
            addWall(gridCoordinate);
        }

        //std::cout << enemies.size() << std::endl;
    }
}

void GridHandler::addWall(sf::Vector2i gridPosition){
        Wall* tempWall = new Wall(sf::Vector2f(gridPosition.x * 32, gridPosition.y * 32));
        tempWall->init();
        std::pair<sf::Vector2i, Wall* > tempValuePair (gridPosition , tempWall);
        walls.insert(tempValuePair);
        pathfinder->addWall(gridPosition);
}

sf::Vector2i GridHandler::toCoordinate(sf::Vector2i position){

    return sf::Vector2i(position.x / GameControl::GRIDSIZE, position.y / GameControl::GRIDSIZE);
}

sf::Vector2i GridHandler::getGridPosition(sf::Vector2i position){
    sf::Vector2i returnVector;
    returnVector.x = position.x - (position.x % GameControl::GRIDSIZE);
    returnVector.y = position.y - (position.y % GameControl::GRIDSIZE);
    return returnVector;
}

//Public
GridHandler::GridHandler(GameControl* gameControl){
    this->gameControl = gameControl;
    pathfinder = new Pathfinder(this);
}

GridHandler::~GridHandler(){
    for(WallMap::iterator it = walls.begin(); it != walls.end(); ++it){
        delete it->second;
    }
	walls.clear();

	if(pathfinder){
        delete pathfinder;
	}
}

void GridHandler::init(){

	if (!txHighlight.loadFromFile("res/img/highlight.png"))
	{
		//std::cout << "Error while loading player texture" << std::endl;
	}
	sprHighlight.setTexture(txHighlight);


    //Setup walls for testing
    for(int i = 1; i < 10; i++){
        addWall(sf::Vector2i(i,1));
        addWall(sf::Vector2i(i,10));

        addWall(sf::Vector2i(10,3 + i));
        addWall(sf::Vector2i(1,1 + i));
    }
}


void GridHandler::update(float delta, sf::Event &event, sf::Vector2i &mousePosition){
    //Handles highlight and mouse position
    sf::Vector2i mouseGridPosition = getGridPosition(mousePosition);
    sprHighlight.setPosition(sf::Vector2f(mouseGridPosition.x,mouseGridPosition.y));

    sf::Mouse mouse;

    //Registers a mouse event every frame, might be nesecarry to change it
    if(mouse.isButtonPressed(sf::Mouse::Left)){
        if(firstMousePress == true){
            attemptToAddWall(mouseGridPosition);
            firstMousePress = false;
        }
    }else{
        firstMousePress = true;
    }

}

void GridHandler::render(sf::RenderWindow &window){
    window.draw(sprHighlight);
    for(WallMap::iterator it = walls.begin(); it != walls.end(); ++it){

        it->second->render(window);
    }
}

std::vector<Wall*> GridHandler::getSurWalls(sf::Vector2i &position){
    std::vector<Wall*> surWalls;

    sf::Vector2i gridPosition = getGridPosition(position);
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

std::deque<sf::Vector2i> GridHandler::getPath(sf::Vector2i startPosition, sf::Vector2i endCoordinate_p){

    sf::Vector2i startCoordinate = toCoordinate( getGridPosition(startPosition) );
    sf::Vector2i endCoordinate = endCoordinate_p;

    return pathfinder->findPath( &startCoordinate, &endCoordinate);
}
