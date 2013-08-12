#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/Enemy.h>

#include <SFML/Graphics.hpp>

#include <vector>

class GameControl;

class EnemyHandler : protected GameObj{
	private:
		GameControl* gameControl;
		std::vector<Enemy*> enemies;
	public:
		EnemyHandler(GameControl* gameControl);
		~EnemyHandler();
		void init();
		void update(float delta);
		void render(sf::RenderWindow &window);
		std::vector<Enemy*>* getEnemies(){ return &enemies;}
		std::deque<sf::Vector2i> getPath(sf::Vector2i position);
};
#endif
