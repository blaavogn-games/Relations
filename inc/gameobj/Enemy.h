#ifndef ENEMY_H
#define ENEMY_H

#include <inc/gameobj/GameObj.h>
#include <inc/col/ColCircle.h>

#include <SFML/Graphics.hpp>

#include <deque>


//Forward declaration
class EnemyHandler;

class Enemy : protected GameObj{
	private:
        signed int const GRIDOFFSET, RADIUS; // -4 , 20
        float const SPEED; //20

		EnemyHandler* enemyHandler;
		ColCircle* colCircle;

        std::deque<sf::Vector2i> path;


		sf::Sprite sprite,sprPath;
		sf::Texture texture, texPath;
		sf::Vector2f position;
        sf::Vector2i targetPoint;
        sf::Vector2f movement;

        void newTargetPoint();

	public:
		Enemy(EnemyHandler* enemyHandler, sf::Vector2i);
		~Enemy();

		void init();
		void update(float delta);
		void render(sf::RenderWindow &window);

        std::deque<sf::Vector2i>* getPath(){return &path;}

        //Set
        void findNewPath();
        void setPath(std::deque<sf::Vector2i>);

        //Closer inheritance between enemy and player might be a good idea, I should do that for next project at least
		sf::Vector2i getPosition();
		ColCircle getColCircle(){return *colCircle;}

};
#endif
