//#include <inc/gameobj/handler/GridHandler.h>
#include <inc/gameobj/GameControl.h>

#include <iostream>

GridHandler::GridHandler(GameControl* gameControl) : firstMousePress(true){
    this->gameControl = gameControl;
}

GridHandler::~GridHandler(){
    for(int y = 0; y < GameControl::GRIDY; y++){
        for(int x = 0; x < GameControl::GRIDX; x++){
            if(grid[x][y]){
                delete grid[x][y];
            }
        }
    }
}

void GridHandler::init(){

    firstMousePress = false;

    pathfinder = new Pathfinder(this);

    //Loading and setting textures, might need some error handling. But if textures arn't loaded the game might as well crash.
	txHighlight.loadFromFile("res/img/highlight.png");
	sprHighlight.setTexture(txHighlight);

    for(int i = 0; i < 6; i++){
        gridTextures[i].loadFromFile("res/img/gridtiles/" + std::to_string(i) + ".png");
    }

    //Creating grid
    for(int y = 0; y < GameControl::GRIDY; y++){
        for(int x = 0; x < GameControl::GRIDX; x++){
            grid[x][y] = new GridTile();
            grid[x][y]->init(&(gridTextures) , sf::Vector2i(x, y));
        }
    }

}

void GridHandler::update(float delta, sf::Vector2i &mousePosition){
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
    for(int y = 0; y < GameControl::GRIDY; y++){
        for(int x = 0; x < GameControl::GRIDX; x++){
            grid[x][y]->render(window);
        }
    }

    window.draw(sprHighlight);
}


//Private
bool GridHandler::attemptToAddWall(sf::Vector2i gridPosition){
    sf::Vector2i coordinate = toCoordinate(gridPosition);

    //Is mouse coordinates within the window
    if(1 <= coordinate.x && coordinate.x < GameControl::GRIDX - 1 && 1 <= coordinate.y &&  coordinate.y < GameControl::GRIDY - 1 && !grid[coordinate.x][coordinate.y]->isWall() ){

        //Adding wall temporarily to do search
        getGrid(&coordinate) -> setTempWall();

        //For friends
        std::vector<Friend*>* friends = gameControl->getFriends();

        for(std::vector<Friend*>::iterator it = friends->begin(); it != friends->end(); ++it){
            sf::Vector2i pointCoordinate = (*it)->getCoordinate();

            if(pointCoordinate.x == coordinate.x && pointCoordinate.y == coordinate.y){
                std::cout << "May not place wall on friend" << std::endl;
                getGrid(&coordinate) -> removeTempWall();
                return false;
            }

            std::deque<sf::Vector2i> tempPath = getPath(sf::Vector2i(14,0), pointCoordinate);
            if(tempPath.size() == 0){
                std::cout << "May not surround friend" << std::endl;
                getGrid(&coordinate) -> removeTempWall();
                return false;
            }

        }

        //For player
        sf::Vector2i playerCoordinate = gameControl->getPlayerCoordinate();
        if(coordinate.x == playerCoordinate.x && coordinate.y == playerCoordinate.y){
            std::cout << "May not place wall on player" << std::endl;
            getGrid(&coordinate) -> removeTempWall();
            return false;
        }

        //For enemies
        //In order for placing a wall following checks should be made
        //1. Get all enemies that has the wallPoint as a point in their path
        // --- Place tempwall
        //1a.If player isn't walled in, place wall

        //2. Does an alternative path exist for all of these enemies?
        //2a     false: don't place wall

        //3. ind make the alternative paths the new paths

        //1.
        std::vector<Enemy*> enemies = gameControl -> getEnemiesWithPathPoint(coordinate);

        //1a
        if( enemies.size() == 0){
            std::deque<sf::Vector2i> tempPath = getPath(sf::Vector2i(14,0), gameControl -> getPlayerCoordinate());

            if(tempPath.size() != 0){
                getGrid(&coordinate) -> removeTempWall();
                addWall(coordinate);
                return true;
            }else{
                std::cout << "Not legal wall yourself in" << std::endl;
                getGrid(&coordinate) -> removeTempWall();
                return false;
            }
        }


        //2
        std::vector<std::deque<sf::Vector2i>> tempPaths;
        for(unsigned int i = 0; i < enemies.size(); i++){
            sf::Vector2i enemyCoordinate = enemies.at(i)->getCoordinate();

            /*if(enemyCoordinate.x == coordinate.x && enemyCoordinate.y == coordinate.y){
                std::cout << "May not place wall on enemy" << std::endl;
                getGrid(&coordinate) -> removeTempWall();
                return false;
            }*/

            std::deque<sf::Vector2i> tempPath = getPath(enemyCoordinate, playerCoordinate);

            if(tempPath.size() != 0){
                tempPaths.push_back( tempPath);
            }else{
                //2a
                std::cout << "Not legal to place wall" << std::endl;
                getGrid(&coordinate) -> removeTempWall();
                return false;
            }
        }


        //3
        for(unsigned int i = 0; i < enemies.size(); i++){
            enemies.at(i) -> setPath(tempPaths.at(i));
        }
        addWall(coordinate);
        return true;
    }
    return false;
}

//Private
void GridHandler::addWall(sf::Vector2i coordinate){
    const int shadowLength = 6;

    grid[coordinate.x][coordinate.y] -> setTexture( &(gridTextures[5]) );
    grid[coordinate.x][coordinate.y] -> setWall();

    gameControl->friendsNewTarget(coordinate);

    //Add shadow tiles
    for(int i = 0; i < shadowLength; i++){
        if(coordinate.y - i >= 0){
            grid[coordinate.x][coordinate.y - i] -> setShadow(1); //From bot
        }
        if(coordinate.y + i < GameControl::GRIDY){
            grid[coordinate.x][coordinate.y + i] -> setShadow(0); //From top
        }
        if(coordinate.x - i >= 0){
            grid[coordinate.x - i][coordinate.y] -> setShadow(3); //From right
        }
        if(coordinate.x + i < GameControl::GRIDX){
            grid[coordinate.x + i][coordinate.y] -> setShadow(2); //From left
        }
    }
}

//Private
sf::Vector2i GridHandler::toCoordinate(sf::Vector2i position){
    return sf::Vector2i(position.x / GameControl::GRIDSIZE, position.y / GameControl::GRIDSIZE);
}

//Private
sf::Vector2i GridHandler::getGridPosition(sf::Vector2i position){
    sf::Vector2i returnVector;
    returnVector.x = position.x - (position.x % GameControl::GRIDSIZE);
    returnVector.y = position.y - (position.y % GameControl::GRIDSIZE);
    return returnVector;
}

//public
std::vector<ColShape*> GridHandler::getSurWalls(sf::Vector2i &coordinate){
    std::vector<ColShape*> surWalls;

    //Get the 3x3 grid expanding from coordinate
    for(int y = coordinate.y - 1; y < coordinate.y + 2; y++){
        for(int x = coordinate.x - 1; x < coordinate.x + 2; x++){
            if(x < GameControl::GRIDX && x >=0 && y < GameControl::GRIDY && y >= 0 ){
                if(grid[x][y] -> isWall()){
                    surWalls.push_back(grid[x][y] -> getCollision());
                }
            }
        }
    }

    return surWalls;
}

//public
std::deque<sf::Vector2i> GridHandler::getPath(sf::Vector2i startCoordinate, sf::Vector2i endCoordinate){
    return pathfinder->findPath(startCoordinate, endCoordinate);
}

bool GridHandler::isWall(int x, int y){

    if(x >= 0 && x < GameControl::GRIDX && y >= 0 && y < GameControl::GRIDY){
        return grid[x][y] -> isWall();
    }else{
        return true;
    }
}
