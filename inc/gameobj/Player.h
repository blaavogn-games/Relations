#ifndef PLAYER_H
#define PLAYER_H

#include <inc/gameobj/ScoreDisplay.h>
#include <inc/gameobj/PersonBase.h>
#include <inc/col/ColCircle.h>
#include <inc/col/Collision.h>

#include <SFML/Graphics.hpp>

#include <vector>

class PlayerHandler;

class Player : public PersonBase{
	private:
        PlayerHandler* playerHandler;

        sf::Vector2i previousCoordinate;

		float speed;

		bool collisionHandler(std::vector<ColShape*>);
        bool looseLife();

	public:
		Player(PlayerHandler*, sf::Vector2f, sf::Texture*);
		~Player();

		void init();
		void update(float delta);

};
#endif
