#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "inc/gameobj/GameControl.h"
#include "inc/gameobj/FpsDisplay.h"
#include "inc/col/ColRectangle.h"

//
int main()
{
    int const TARGET_FPS = 60;

    GameControl* gameControl = new GameControl();
    gameControl->init();

    FpsDisplay fpsDisplay;
    fpsDisplay.init();

    sf::Clock clock;
    float deltaTime;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Spil", sf::Style::Close);
    sf::Vector2i mousePosition;

    window.setFramerateLimit(TARGET_FPS);

    //Gameloop
    while (window.isOpen())
    {
        /*The idea of this gameloop is two have to "phases"
        1a. Prepare deltaTime and Input
        1b. Updating all gameObjects with delta time and input
        2. Render all necesarry gameObjects*/

        //Handles delta-time
        deltaTime = clock.restart().asSeconds();
        sf::Event event;

        //Get events and handles close??
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        mousePosition = sf::Mouse::getPosition() - window.getPosition();

        gameControl->update(deltaTime, event, mousePosition);
        fpsDisplay.update(deltaTime);

        window.clear(sf::Color(12,12,100,255));

        //Rendering in layer
        gameControl->render(window);
        fpsDisplay.render(window);

        //Diplay has a delay that targets the target FPS
        window.display();

    }

    return 0;
}
