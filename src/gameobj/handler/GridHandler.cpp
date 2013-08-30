#include <inc/gameobj/handler/GridHandler.h>
#include <inc/gameobj/GameControl.h>

#include <iostream>

GridHandler::GridHandler(GameControl* gameControl) : firstMousePress(true){
    this->gameControl = gameControl;
}

GridHandler::~GridHandler(){
    for(int y = 0; y < GameControl::GRIDY; y++){
        for(int x = 0; x < GameControl::GRIDX; x++){
            delete grid[x][y];
        }
    }

	if(pathfinder){
        delete pathfinder;
	}
}

void GridHandler::init(){

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
            grid[x][y]->init(&(gridTextures[0]) , sf::Vector2i(x, y));
        }
    }

    //Setup walls for testing
//    for(int i = 1; i < 10; i++){
//        addWall(sf::Vector2i(i,1));
//        addWall(sf::Vector2i(i,10));
//        addWall(sf::Vector2i(10,3 + i));
//        addWall(sf::Vector2i(1,1 + i));
//    }
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
    for(int y = 0; y < GameControl::GRIDY; y++){
        for(int x = 0; x < GameControl::GRIDX; x++){
            grid[x][y]->render(window);
        }
    }

    window.draw(sprHighlight);

}


//Private
void GridHandler::attemptToAddWall(sf::Vector2i gridPosition){
    sf::Vector2i coordinate = toCoordinate(gridPosition);

    //Is mouse coordinates within the window
    if(1 <= coordinate.x && coordinate.x < GameControl::GRIDX - 1 && 1 <= coordinate.y &&  coordinate.y < GameControl::GRIDY - 1 && !grid[coordinate.x][coordinate.y]->isWall() ){

        //For points
        std::vector<Point*>* points = gameControl->getPoints();

        for(std::vector<Point*>::iterator it = points->begin(); it != points->end(); ++it){
            sf::Vector2i pointCoordinate = (*it)->getCoordinate();
            if(pointCoordinate.x == coordinate.x && pointCoordinate.y == coordinate.y){
                return;
                //Not legaæ, perhaps delete
            }
        }


        //For enemies
        //In order for placing a wall following checks should be made
        //1. Get all enemies that has the wallPoint as a point in their path
        //1a.      if 0: Place wall

        //2. Does an alternative path exist for all of these enemies?
        //2a     false: don't place wall

        //3. Place wall and find make the alternative paths the new paths

        //1.
        std::vector<Enemy*> enemies = gameControl -> getEnemiesWithPathPoint(coordinate);

        //1a
        if( enemies.size() == 0){
            addWall(coordinate);
            return;
        }

        //Adding wall temporarily to do search
        getGrid(&coordinate) -> setTempWall();

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

                getGrid(&coordinate) -> removeTempWall();

                legalWall = false;
                break;
            }
        }

        //3
        if(legalWall){
            for(unsigned int i = 0; i < enemies.size(); i++){
                enemies.at(i) -> setPath(tempPaths.at(i));
            }
            addWall(coordinate);
        }
    }
}

//Private
void GridHandler::addWall(sf::Vector2i coordinate){

    grid[coordinate.x][coordinate.y] -> setTexture( &(gridTextures[5]) );
    grid[coordinate.x][coordinate.y] -> setWall();
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
std::vector<ColShape*> GridHandler::getSurWalls(sf::Vector2i &position){
    std::vector<ColShape*> surWalls;

    sf::Vector2i gridPosition = getGridPosition(position);
    sf::Vector2i coordinate = toCoordinate(gridPosition);

    //Get the 2x2 grid expanding from coordinate
    for(int y = coordinate.y; y < coordinate.y + 2; y++){
        for(int x = coordinate.x; x < coordinate.x + 2; x++){
            if(x < GameControl::GRIDX && y < GameControl::GRIDY){
                if(grid[x][y] -> isWall()){
                    surWalls.push_back(grid[x][y] -> getCollision());
                }
            }
        }
    }

    return surWalls;
}

//public
std::deque<sf::Vector2i> GridHandler::getPath(sf::Vector2i startPosition, sf::Vector2i endCoordinate_p){
    sf::Vector2i startCoordinate = toCoordinate( getGridPosition(startPosition) );
    sf::Vector2i endCoordinate = endCoordinate_p;

    return pathfinder->findPath( startCoordinate, endCoordinate);
}
