#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#include <inc/gameobj/GameObj.h>
#include <inc/gameobj/Friend.h>
#include <inc/gameobj/Enemy.h>
#include <inc/gameobj/Player.h>

#include <SFML/Graphics.hpp>

class GameControl; // Forward


class PlayerHandler : public GameObj{
    private:
        GameControl* gameControl;
        Player* player;
        ScoreDisplay* scoreDisplay;

        int lives;
        std::vector<sf::Sprite*> sprLives;

        sf::Texture texPlayer;
		sf::Texture texLife;

        int const MAXLIVES;
    public:
        PlayerHandler(GameControl*);
        ~PlayerHandler();

        void init();
        void update(float delta);
        void render(sf::RenderWindow &window);
        void reset();

        void addScore(float, sf::Vector2f);
        bool looseLife();
        void death();

        void wallAdded();
        sf::Vector2i getPlayerCoordinate();
};

#endif
