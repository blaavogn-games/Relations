#include <inc/gameobj/GameControl.h>
#include <inc/gameobj/GridTile.h>

GridTile::GridTile(){
    wall = false;
}
GridTile::~GridTile(){
    delete collision;
}

void GridTile::init(sf::Texture* texture, sf::Vector2f position){
    this->position = position;

    sprite.setTexture(*texture);
    sprite.setPosition(position);
}

void GridTile::render(sf::RenderWindow &window){
    window.draw(sprite);
}

//public
void GridTile::setTexture(sf::Texture* texture){
    sprite.setTexture(*texture);
}

//public
void GridTile::setWall(){
    wall = true;
    collision = new ColRectangle(position, GameControl::GRIDSIZE, GameControl::GRIDSIZE);
}
