#include <inc/gameobj/ScoreDisplay.h>
#include <sstream>

ScoreDisplay::ScoreDisplay(){}
ScoreDisplay::~ScoreDisplay(){
    for(std::vector<ScoreMsg*>::iterator it = scoreMsgs.begin(); it != scoreMsgs.end(); ++it){
        delete (*it);
    }

    scoreMsgs.clear();
}

void ScoreDisplay::init(){
    font.loadFromFile("res/fonts/SW721BTB.OTF");
    texBg.loadFromFile("res/img/player/scoreBG.png");
    scoreTex.loadFromFile("res/img/player/score.png");

    scoreBuffer.loadFromFile("res/sound/score.ogg");
    scoreSound.setBuffer(scoreBuffer);


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

void ScoreDisplay::update(float delta){
    std::vector<ScoreMsg*>::iterator it = scoreMsgs.begin();

    while(it != scoreMsgs.end()){
        (*it)->update(delta);

        if((*it) ->timer > 1){
            delete (*it);
            it = scoreMsgs.erase(it);
        }else{
            it++;
        }

    }
}


void ScoreDisplay::render(sf::RenderWindow &window){
    for(std::vector<ScoreMsg*>::iterator it = scoreMsgs.begin(); it != scoreMsgs.end(); ++it){
        (*it)->render(window);
    }

    if(dead){
        window.draw(bg);
        window.draw(minorText);
    }
    window.draw(displayText);
}


void ScoreDisplay::death(){
    dead = true;
    displayText.setPosition(290,250);
    displayText.setCharacterSize(50);

}


void ScoreDisplay::addScore(float points, sf::Vector2f playerPosition){
    if(points >= 1){
        scoreSound.play();
        ScoreMsg* tempMsg = new ScoreMsg();
        tempMsg -> init(playerPosition, &scoreTex);
        scoreMsgs.push_back(tempMsg);
    }

    fScore += points;
    iScore = (int) fScore;
}
