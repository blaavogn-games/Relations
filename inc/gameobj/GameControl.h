#ifndef GAMECONTROL_H
#define GAMECONTROL_H
#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/Player.h>
#include <inc/gameobj/handler/EnemyHandler.h>
#include <inc/gameobj/handler/GridHandler.h>

#include <deque>
#include <vector>


//GameControl is becomming a path for communication between my handlers.
//Maybe it is better to let the handlers have a pointer to eachother?
class GameControl : protected GameObj{
	public:
        static const int GRIDSIZE = 32, GRIDX = 25, GRIDY = 19;
		GameControl();
		~GameControl();

		void init();
		void update( float delta, sf::Event &event, sf::Vector2i &mousePosition);
		void render(sf::RenderWindow &window);

        //EnemyHandler connection pipe
		std::vector<Enemy*>* getEnemies();
		std::vector<Enemy*> getEnemiesWithPathPoint(sf::Vector2i);
        void enemiesFindNewPath();

        //GridHandler connection pipe
        std::deque<sf::Vector2i> getPath(sf::Vector2i);
		std::vector<ColShape*> getSurWalls(sf::Vector2i position);

        //Player connection pipe
        sf::Vector2i getPlayerCoordinate();

	private:
		Player* player;
		EnemyHandler* enemyHandler;
		GridHandler* gridHandler;
};
#endif
