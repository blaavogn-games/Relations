#ifndef ENEMY_H
#define ENEMY_H

#include <inc/gameobj/PersonBase.h>
#include <inc/col/ColCircle.h>

#include <SFML/Graphics.hpp>

#include <deque>


//Forward declaration
class EnemyHandler;

class Enemy : public PersonBase{
	private:
        float const SPEED; //20

		EnemyHandler* enemyHandler;

        std::deque<sf::Vector2i> path;

		sf::Sprite sprPath;
		sf::Texture texPath;
        sf::Vector2i targetPoint;
        sf::Vector2f movement;

        void newTargetPoint();

	public:
		Enemy(EnemyHandler* enemyHandler, sf::Vector2f, sf::Texture*);
		~Enemy();

		void init();
		void update(float delta);
		void render(sf::RenderWindow &window);

        std::deque<sf::Vector2i>* getPath(){return &path;}

        //Set
        void findNewPath();
        void setPath(std::deque<sf::Vector2i>);


};
#endif
