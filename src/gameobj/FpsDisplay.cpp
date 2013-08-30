#include <inc/gameobj/FpsDisplay.h>
#include <sstream>

void FpsDisplay::init(){
    if (!font.loadFromFile("res/fonts/sansation.ttf")){
        //UNhandled error
    }
}

void FpsDisplay::update(float delta){
    fps = (int) (1.0f / delta);
}

void FpsDisplay::render(sf::RenderWindow &window){
    std::ostringstream ss;
    ss << "FPS: " << fps;
    sf::Text displayText;
    displayText.setFont(font);
    displayText.setCharacterSize(16);
    displayText.setStyle(sf::Text::Bold);
    displayText.setColor(sf::Color::White);
    displayText.setPosition(6,570);
    displayText.setString(ss.str());

    window.draw(displayText);

}
