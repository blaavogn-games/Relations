#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/Enemy.h>
#include <inc/alarm/Alarm.h>

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <vector>

class GameControl;

class EnemyHandler : public GameObj{
	private:
		GameControl* gameControl;
		std::vector<Enemy*> enemies;
		sf::Texture texEnemy;


	public:
		EnemyHandler(GameControl* gameControl);
		~EnemyHandler();
		void init();
		void update(float delta);
		void render(sf::RenderWindow &window);
        void addEnemy(sf::Vector2f);
        void reset();

        //Set more or less
        void findNewPaths();

        //Get
		std::deque<sf::Vector2i> getPath(sf::Vector2i coordinate);
        std::vector<Enemy*> getEnemiesWithPathPoint(sf::Vector2i);
        std::vector<Enemy*>* getEnemies(){ return &enemies;}

};
#endif
