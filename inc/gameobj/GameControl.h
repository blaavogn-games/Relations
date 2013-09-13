#ifndef GAMECONTROL_H
#define GAMECONTROL_H
#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/handler/PlayerHandler.h>
#include <inc/gameobj/handler/EnemyHandler.h>
#include <inc/gameobj/handler/GridHandler.h>
#include <inc/gameobj/handler/FriendHandler.h>

#include <deque>
#include <vector>


//GameControl is becomming a path for communication between my handlers.
//Maybe it is better to let the handlers have a pointer to eachother?
class GameControl : public GameObj{
	public:
        static const int GRIDSIZE = 32, GRIDX = 25, GRIDY = 19;
		GameControl();
		~GameControl();

		void init();
		void update(float delta, sf::Vector2i &mousePosition);
		void render(sf::RenderWindow &window);

        void pauseGame();
        void resetGame();

        //Next project this should just be getHandlerX this seems stupid
        //EnemyHandler connection pipe
		std::vector<Enemy*>* getEnemies();
		std::vector<Enemy*> getEnemiesWithPathPoint(sf::Vector2i);
        void enemiesFindNewPath();
        void addEnemy(sf::Vector2f);

        //GridHandler connection pipe
        std::deque<sf::Vector2i> getPath(sf::Vector2i);
		std::vector<ColShape*> getSurWalls(sf::Vector2i coordinate);
		GridTile* getGrid(sf::Vector2i*);
		bool isWall(int x, int y);

        //FriendHandler pipe
        std::vector<Friend*>* getFriends();
        void friendsNewTarget(sf::Vector2i);

        //Player connection pipe
        sf::Vector2i getPlayerCoordinate();


	private:
		PlayerHandler* playerHandler;
		EnemyHandler* enemyHandler;
		GridHandler* gridHandler;
		FriendHandler* friendHandler;

        bool pause, pausePress, resetPress;

        void clearGame();

};
#endif
