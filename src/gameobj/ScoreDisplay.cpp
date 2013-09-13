#include <inc/gameobj/ScoreDisplay.h>
#include <sstream>

ScoreDisplay::ScoreDisplay(){}
ScoreDisplay::~ScoreDisplay(){}

void ScoreDisplay::init(){
    font.loadFromFile("res/fonts/sansation.ttf");

    displayText.setFont(font);
    displayText.setCharacterSize(16);
    displayText.setStyle(sf::Text::Bold);
    displayText.setColor(sf::Color::White);
    displayText.setPosition(6,0);

    fScore = 0;
    iScore = 0;
}

void ScoreDisplay::update(float delta){

}

void ScoreDisplay::render(sf::RenderWindow &window){
    std::ostringstream ss;
    ss << "Score: " << iScore;
    displayText.setString(ss.str());

    window.draw(displayText);

}

void ScoreDisplay::addScore(float points){
    fScore += points;
    iScore = (int) fScore;
}
