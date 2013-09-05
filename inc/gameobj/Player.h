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
		ColShape* col;
        ScoreDisplay* scoreDisplay;

        sf::Vector2f const CENTER;
        int const MAXLIVES;

		sf::Sprite sprPlayer;
		sf::Texture texPlayer, texLife;
		sf::Vector2f position;
        sf::Vector2i previousCoordinate;

        std::vector<sf::Sprite*> lives;

		float rotation,speed;

		void setRotation(sf::Vector2f);
        bool collisionHandler(std::vector<ColShape*>);
        bool looseLife();

	public:
		Player(GameControl* gameControl);
		~Player();

		void init();
		void update(float delta);
		void render(sf::RenderWindow &window);

        //Get
        ColShape* getCol();
        sf::Vector2i getPosition(); //Should be changed
        sf::Vector2i getCoordinate();
};
#endif
