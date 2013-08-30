#ifndef PLAYER_H
#define PLAYER_H


#include <inc/gameobj/ScoreDisplay.h>
#include <inc/gameobj/GameObj.h>
#include <inc/col/ColCircle.h>
#include <inc/col/Collision.h>

#include <SFML/Graphics.hpp>

#include <vector>


class GameControl;

class Player : public GameObj{
	private:
		GameControl* gameControl;
		ColCircle* colCircle;
        ScoreDisplay* scoreDisplay;

		sf::Sprite sprPlayer;
		sf::Texture texPlayer, texLife;
		sf::Vector2f position;
        sf::Vector2i previousCoordinate;

        std::vector<sf::Sprite*> lives;

		float speed;
        int const RADIUS, MAXLIVES;


        bool collisionHandler(std::vector<ColShape*>);
        void looseLife();

	public:
		Player(GameControl* gameControl);
		~Player();

		void init();
		void update(float delta);
		void render(sf::RenderWindow &window);

        //Get
        ColCircle* getCol();
        sf::Vector2i getPosition();
        sf::Vector2i getCoordinate();
};
#endif
