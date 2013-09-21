#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include <inc/gameobj/ProgramControl.h>
#include <inc/gameobj/FpsDisplay.h>

int main()
{
    int const TARGET_FPS = 60;

    ProgramControl* programControl = new ProgramControl();
    programControl->init();

  //  FpsDisplay fpsDisplay;
  //  fpsDisplay.init();

    sf::Clock clock;
    float deltaTime;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Relations", sf::Style::Close);
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

        mousePosition = sf::Mouse::getPosition(window);

        programControl->update(deltaTime, mousePosition);
    //    fpsDisplay.update(deltaTime);

        //Rendering in layer
        programControl->render(window);
      //  fpsDisplay.render(window);

        //Diplay has a delay that targets the target FPS
        window.display();

    }

    return 0;
}
