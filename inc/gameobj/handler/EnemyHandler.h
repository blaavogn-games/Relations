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
		Alarm* alarm;

        void addEnemy();

	public:
		EnemyHandler(GameControl* gameControl);
		~EnemyHandler();
		void init();
		void update(float delta);
		void render(sf::RenderWindow &window);
        void alarmAction(int type);

        //Set more or less
        void findNewPaths();

        //Get
		std::deque<sf::Vector2i> getPath(sf::Vector2i position);
        std::vector<Enemy*> getEnemiesWithPathPoint(sf::Vector2i);
        std::vector<Enemy*>* getEnemies(){ return &enemies;}

};
#endif
