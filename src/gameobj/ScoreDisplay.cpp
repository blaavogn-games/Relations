#include <inc/gameobj/ScoreDisplay.h>
#include <sstream>

ScoreDisplay::ScoreDisplay(){}
ScoreDisplay::~ScoreDisplay(){}

void ScoreDisplay::init(){
    font.loadFromFile("res/fonts/SW721BTB.OTF");
    texBg.loadFromFile("res/img/player/scoreBG.png");

    bg.setTexture(texBg);
    bg.scale(800,600);
    bg.setPosition(0,0);

    dead = false;

    displayText.setFont(font);
    displayText.setCharacterSize(20);
    displayText.setColor(sf::Color::Black);
    displayText.setPosition(16,10);

    minorText.setFont(font);
    minorText.setCharacterSize(20);
    minorText.setColor(sf::Color::Black);
    minorText.setPosition(260,320);

    fScore = 0;
    iScore = 0;

    std::ostringstream ss, ss2;
    ss << "Score: " << iScore;
    displayText.setString(ss.str());

    ss2 << "-- Press Space To Continue --";
    minorText.setString(ss2.str());
}

void ScoreDisplay::death(){
    dead = true;
    displayText.setPosition(290,250);
    displayText.setCharacterSize(50);


}

void ScoreDisplay::render(sf::RenderWindow &window){
    if(dead){
        window.draw(bg);
        window.draw(minorText);
    }
    window.draw(displayText);
}

void ScoreDisplay::addScore(float points){
    fScore += points;
    iScore = (int) fScore;
}
