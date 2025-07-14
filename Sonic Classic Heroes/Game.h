#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

//#include "Player.h"
#include"level1.h"
#include "level2.h"
#include "level3.h"
#include "boss_level.h"
#include"Menu.h"
#include"Sonic.h"
#include "Tails.h"
#include "knuckles.h"


#include "Scorings.h"

#include "levels.h"


#include "Player.h"



using namespace sf;
using namespace std;
class Game
{

    // Private data members

    float dt;

    RenderWindow window;
    Event ev;
    int screen_x = 1200, screen_y = 900;
    const int cell_size;
    float gravity, terminal_Velocity;
    float scale_x, scale_y;
    int raw_img_x, raw_img_y;
    int Pheight, Pwidth;
    int hit_box_factor_x, hit_box_factor_y;

    //Music lvlMus;
   

    Music* lvlMus;


    bool inFlight = false;
    bool firstHit = false;

    //View v;
    Clock animationClock;


    Music jumpMusic;

    float offset_y = 0;
    float velocityY = 0;
    float velocityY2 = 0;
    float velocityY3 = 0;
    bool onGround = false;
    bool onGround2 = false;
    bool onGround3 = false;
    bool jumping;
    bool jumping2;
    bool jumping3;
    bool leftMovement;
    bool rightMovement;
    bool knuckleLeft;
    bool startofTheGame;
    bool onSpring;
    bool bottomCollision;

   /* Vector2f initialMain_character;
    Vector2f initialOther1;
    Vector2f initialOther2;*/


    float initial_main_x;
    float initial_main_y;

    float initial_other1_x;
    float initial_other1_y;

    float initial_other2_x;
    float initial_other2_y;


    bool save_game;
    bool load_save_game;
   
    const int max_character = 3;
    int main_character_index;
    int other1;
    int other2;

    int levelIndex;

    Clock tailsClock;
    Clock standClock;

    Sonic obj;
    knuckles obj3;
    Tails obj1;
    //level1 level;
    Menu mainMenu;

    Player** character;
    levels** lvl;

    Scorings* highlight;

    Clock frameClock;

    void reset();
    //Overload
    void reset(levels** lvl);


    // Function to chekc if the game over properties are being fulllfilled or not
    bool GameOver(float& y, bool& startOfgame, float timeleft, levels** lvl);
    bool startOflevel;

    int ringCount;
    int score;

    // Friction to be used in levels
    float friction;


    // Function to load the saved game
    void loadGame();

public:

    // COnstructo
    Game();
    virtual ~Game();


    // Memver functiosn
    void run();
    void update();
    void render();


    
};

