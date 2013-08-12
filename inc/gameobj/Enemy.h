#ifndef ENEMY_H
#define ENEMY_H

#include <inc/gameobj/GameObj.h>
#include <inc/col/ColCircle.h>

#include <SFML/Graphics.hpp>

class Enemy : protected GameObj{
	private:
        int const GRIDOFFSET = 9;
		ColCircle* colCircle;

		sf::Sprite sprite;
		sf::Texture texture;
		sf::Vector2f position;

	public:
		Enemy(sf::Vector2i);
		~Enemy();

		void init();
		void update(float delta);
		void render(sf::RenderWindow &window);
		ColCircle getColCircle(){return *colCircle;}
};
#endif
