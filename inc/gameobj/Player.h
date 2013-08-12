#ifndef PLAYER_H
#define PLAYER_H

#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/Wall.h>
#include <inc/col/ColCircle.h>
#include <inc/col/Collision.h>

#include <SFML/Graphics.hpp>

#include <vector>


class GameControl;

class Player : protected GameObj{
	private:
		sf::Sprite sprite;
		sf::Texture texture;
		sf::Vector2f position;

		GameControl* gameControl;
		ColCircle* colCircle;

		float speed;

        bool collisionHandler(std::vector<Wall*>);

	public:
		Player(GameControl* gameControl);
		~Player();

		void init();
		void update(float delta);
		void render(sf::RenderWindow &window);
        ColCircle* getCol();
        sf::Vector2i getPosition();
};
#endif
