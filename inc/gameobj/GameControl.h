#ifndef GAMECONTROL_H
#define GAMECONTROL_H
#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/Player.h>
#include <inc/gameobj/handler/EnemyHandler.h>
#include <inc/gameobj/handler/WallHandler.h>

#include <deque>
#include <vector>

class GameControl : protected GameObj{
	public:
        static const int GRIDSIZE = 32, GRIDX = 25, GRIDY = 19;
		GameControl();
		~GameControl();

		void init();
		void update( float delta, sf::Event &event, sf::Vector2i &mousePosition);
		void render(sf::RenderWindow &window);
		std::vector<Enemy*>* getEnemies();
		std::vector<Wall*> getSurWalls(sf::Vector2i position);
        std::deque<sf::Vector2i> getPath(sf::Vector2i);

	private:
		Player* player;
		EnemyHandler* enemyHandler;
		WallHandler* wallHandler;
};
#endif
