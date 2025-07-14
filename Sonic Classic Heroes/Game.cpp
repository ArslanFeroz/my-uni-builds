#include "Game.h"

#include <iostream>

void Game::loadGame()
{

    lvlMus[levelIndex].setVolume(0);

    // Opening the file
    std::ifstream myfile("Data/data.txt");
   
    
    // Extracting data into the required vvaribles
    float x0, y0, x1, y1, x2, y2;
    int   h0, h1, h2;
    myfile >> x0 >> y0 >> h0
        >> x1 >> y1 >> h1
        >> x2 >> y2 >> h2;



    std::string sBrain, sBee, sBug, sCrab, sRing;
    myfile >> sBrain >> sBee >> sBug >> sCrab >> sRing;

    int savedLevel, savedScore, ringCount;

    myfile >> savedLevel >> savedScore >> ringCount;
    levelIndex = savedLevel;
    score = savedScore;

    std::cout << "Ring counts file : " << sRing << std::endl;


    // Appying the properties of each player
    character[0]->loadFromSave(x0, y0, h0);
    character[1]->loadFromSave(x1, y1, h1);
    character[2]->loadFromSave(x2, y2, h2);

  
    // Applying the properties to enemies and collectibles like rings
    lvl[levelIndex]->loadEnemyStatuses(sBrain, sBee, sBug, sCrab, sRing, ringCount);

   /* for (int i = 0; i < 4; ++i)
        lvl[i]->reset();*/

    //cout << "Playing the lvl music of " << levelIndex << " to " << endl;
   /* lvlMus[levelIndex].play();
    lvlMus[levelIndex].setVolume(30);*/


    lvl[levelIndex]->setClock();
}

Game::Game() : window(VideoMode(1200, 900), "Sonic the Hedgehog-OOP", Style::Close), cell_size(64)
, gravity(1.f)
, terminal_Velocity(20.f)
, scale_x(2.5f)
, scale_y(2.5f)
, raw_img_x(24)
, raw_img_y(35)
, ringCount(0)
, save_game(false)
, load_save_game(false)
, friction(100)
{

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // Load level music
  /*  if (!lvlMus.openFromFile("Data/labrynth.ogg")) {
        std::cout << "Failed to lead the music" << std::endl;
        return;
    }
    lvlMus.setVolume(30);
    lvlMus.setLoop(true);
    lvlMus.play();*/
   


    // Musics to be used in each level
    lvlMus = new Music [4];
    lvlMus[0].openFromFile("Data/labrynth.ogg");
    lvlMus[1].openFromFile("Data/pasta.ogg");
    lvlMus[2].openFromFile("Data/pasta.ogg");
    lvlMus[3].openFromFile("Data/bossLevel.ogg");

    for (int i = 0; i < 4; i++) {
        lvlMus[i].setLoop(true);
        lvlMus[i].setVolume(0);
        lvlMus[i].play();
    }
    
   


    // Music to play when the player jumps
    jumpMusic.openFromFile("Data/Jump.wav");
    jumpMusic.setVolume(40);

    // Calculate player hitbox dimensions
    Pheight = raw_img_y * scale_y;
    Pwidth = raw_img_x * scale_x;
    hit_box_factor_x = int(8 * scale_x);
    hit_box_factor_y = int(5 * scale_y);
    
    // Center view on player
   /* v.setSize(screen_x, screen_y);
    v.setCenter(obj.getPosition());*/

    // Initialize state

    // ALl the necessary boolean var to be used for various purposes
    startofTheGame = true;
    jumping = false;
    jumping2 = false;
    jumping3 = false;
    leftMovement = false;
    rightMovement = true;
    knuckleLeft = false;
    onSpring = false;
    bottomCollision = false;
    startOflevel = true;

    /*initialMain_character.x = 200; initialMain_character.y = 100;
    initialOther1.x = 150;  initialOther1.y = 100;
    initialOther2.x = 105; initialOther2.y = 100;*/


    // Initial posiitons of all the playerss
    initial_main_x = 200;
    initial_main_y = 100;

    initial_other1_x = 150;
    initial_other1_y = 100;

    initial_other2_x = 105;
    initial_other2_y = 100;

    //score = new int(0);
    score = 0;

    main_character_index = 0;
    other1 = (main_character_index + 1) % 3;
    other2 = (main_character_index + 2) % 3;


    // Making the characters
    character = new Player * [3];
    character[0] = new Sonic;
    character[1] = new Tails;
    character[2] = new knuckles;


    //  Making the levels
    lvl = new levels * [4];
    lvl[0] = new level1;
    lvl[1] = new level2;
    lvl[2] = new level3;
    lvl[3] = new boss_level;

    levelIndex = 0;


    highlight = new Scorings;


    // animation and tail's filight clock
    animationClock.restart();
    tailsClock.restart();

}

Game::~Game()
{

    // freeing the memories
    for (int i = 0; i < max_character; i++) {
        delete character[i];
    }

    delete[]character;


    for (int i = 0; i < 4; i++) {
        delete lvl[i];
    }
    delete[]lvl;

    delete[]lvlMus;

    delete highlight;
}


void Game::reset()
{

    // This function only resets the positions and players state back to default during level up
    //lvl.reset();

    main_character_index = 0;
    other1 = 1;
    other2 = 2;

    character[0]->setPosition(initial_main_x, initial_main_y);
    character[1]->setPosition(initial_other1_x, initial_other1_y);
    character[2]->setPosition(initial_other2_x, initial_other2_y);

    //character[0]->setPosition(initialMain_character);
    //character[1]->setPosition(initialOther1);
    //character[2]->setPosition(initialOther2);

    character[0]->setHealth(3);
    character[1]->setHealth(3);
    character[2]->setHealth(3);

    jumping = jumping2 = jumping3 = false;
    onGround = onGround2 = onGround3 = false;

    //for (int i = 0; i < 4; i++) {
    //    //lvlMus[levelIndex].setVolume(0);
    //    lvlMus[levelIndex].stop();
    //}

    /* v.setCenter(initialMain_character);
     window.setView(v);*/


}

// overload of the previous functions
void Game::reset(levels** lvl)
{
    for (int i = 0; i < 4; i++) {
        lvl[i]->reset();
    }

    levelIndex = 0;
    startOflevel = true;
    ringCount = 0;

    main_character_index = 0;
    other1 = 1;
    other2 = 2;

    character[0]->setPosition(initial_main_x, initial_main_y);
    character[1]->setPosition(initial_other1_x, initial_other1_y);
    character[2]->setPosition(initial_other2_x, initial_other2_y);

    character[0]->setHealth(3);
    character[1]->setHealth(3);
    character[2]->setHealth(3);


    //for (int i = 0; i < 4; i++) {
    //    //lvlMus[levelIndex].setVolume(0);
    //    lvlMus[levelIndex].stop();
    //}

    //score = 0;

    jumping = jumping2 = jumping3 = false;
    onGround = onGround2 = onGround3 = false;


}

bool Game::GameOver(float& y, bool& startOfgame, float timeleft, levels** lvl)
{

    // as all levels have 14 totals rows their height becaome to be 750, to so if playersgoes beyond it, he fell into a pit
    if (y >= 750 || timeleft <= 0) {


        if (y >= 750) {
            cout << " The game is over because of the pitfall" << endl;
        }

        if (timeleft <= 0) {
            cout << "The game is over because of the time limit" << endl;
        }

        startOfgame = true;
        //lvl[levelIndex]->reset();
        lvlMus[levelIndex].setVolume(0);
        reset(lvl);
        return true;
    }
    return false;
}

//bool Game::GameOver(float& y, bool& startOfgame, float timeleft, char** lvl);
//{
//    if (y >= 750 || timeleft) {
//        startOfgame = true;
//        
//        return true;
//    }
//    return false;
//}

void Game::run()
{

    //// Building all the levels in advance
    //for (int i = 0; i < 2; i++) {
    //    lvl[i]->builLevel();
    //}

    // Mian game loop
    while (window.isOpen()) {

        // Calculating the delta time being used for accelerations adn de accelerations
        dt = frameClock.restart().asSeconds();

        update();
        render();
    }
}

void Game::update()
{
    if (onGround)
        jumping = false;

    // Setting the player pointer and score pointer
    for (int i = 0; i < 4; i++) {
        lvl[i]->setPlayer(character[main_character_index]);
        lvl[i]->setScore(&score);
    }

    mainMenu.setScore(&score);

    knuckles* k = dynamic_cast<knuckles*>(character[2]);


    // If it is the start of the level then, resetting its clock
    if (startOflevel && !startofTheGame) {

       /* cout << "Setting the level of " << levelIndex << " to zero" << endl;

        lvlMus[levelIndex].stop();*/

        lvlMus[levelIndex].setVolume(30);

        
        std::cout << "In the level clock reset " << std::endl;
        lvl[levelIndex]->setClock();


       /* lvlMus[levelIndex].stop();
        lvlMus[levelIndex].play()*/

        //lvl[levelIndex]->playMusic(levelIndex);
        startOflevel = false;

    }


    // Changing the friction, and gravity base on the the level
    switch (levelIndex)
    {

    case 0: friction = 60;
        gravity = 1.f;
        break;

    case 1: friction = 40;
        gravity = 1.f;
        break;
    case 2: friction = 60;
        gravity = 0.5;
        break;
    case 3: friction = 60;
        gravity = 1.f;
    default:
        break;
    }

    //lvl[levelIndex]->playMusic(levelIndex);
   

    // Reating to different events
    while (window.pollEvent(ev))
    {

        if (ev.type == Event::KeyPressed) {


            if (main_character_index == 2) {

                bool motionLeft = false;
                if (!rightMovement)
                    motionLeft = true;

                int index1, index2;

                // function to see if the next tile is a breakable walls
                bool sawWall = character[main_character_index]->breakAblewall(lvl[levelIndex]->getLevel(), character[main_character_index]->getPosition_x() + character[main_character_index]->getVelocity_x(), character[main_character_index]->getPosition_y(), Pwidth, Pheight, hit_box_factor_x, hit_box_factor_y, cell_size, index1, index2, motionLeft);
                character[main_character_index]->setIndexes(index1, index2);

                //if (sawWall) {
                //    //std::cout << "Saw a breakable wall at indexes : " << index1 << " " << index2 << std::endl;
                //}

                if (sawWall) {
                    character[main_character_index]->SpecialAbilities(ev, lvl[levelIndex]->getLevel(), motionLeft);

                }
                else {
                    k->setPunchingStatus();
                }
               
            }
            else if (main_character_index == 1) {

                character[main_character_index]->SpecialAbilities(ev);
            }

            else
            {
                character[main_character_index]->SpecialAbilities(ev);

            }




            // changing the character
            character[main_character_index]->shiftCharacter(ev, main_character_index, other1, other2);

            if (ev.key.code == Keyboard::Escape) {

                mainMenu.PauseMenu(window, startofTheGame, save_game);
                if (startofTheGame) {

                    lvlMus[levelIndex].setVolume(0);
                    reset(lvl);

                }
                    //reset(level);
            }
        }


        bool motionLeft;
        if (rightMovement)
            motionLeft = false;
        else
            motionLeft = true;


        //character[main_character_index]->SpecialAbilities(ev, level.getLevel(), motionLeft);


        if (ev.type == Event::Closed)
        {
            window.close();
        }

        if (ev.type == Event::KeyReleased) {
            // Changing the state of the sprite

            character[main_character_index]->Still_State(ev);
            character[other1]->Still_State(ev);
            character[other2]->Still_State(ev);
            //obj.Still_State(ev);
           /* obj1.Still_State(ev);
            obj3.Still_State(ev);*/
        }
    }



    std::string state;

    // If the space key is pressed or stand on the spring then the player jumps
    if (Keyboard::isKeyPressed(Keyboard::Space) || onSpring) {

        jumpMusic.play();

        if (!jumping) {

            /*We will call the jump function over here*/
            inFlight = true;
            firstHit = true;

            jumping = true;
            character[main_character_index]->jump(jumping, onGround, gravity, lvl[levelIndex]->getLevel(), Pwidth, hit_box_factor_x, hit_box_factor_y, cell_size, onSpring);
            onSpring = false;
            //obj.jump(jumping, onGround, gravity);
            if (rightMovement)
                state = "R";
            else
                state = "L";

            character[main_character_index]->jumpState(state, animationClock);

        }


        if (!jumping2) {
            jumping2 = true;
            //obj1.jump(jumping2, onGround2, gravity);
            character[other1]->jump(jumping2, onGround2, gravity, lvl[levelIndex]->getLevel(), Pwidth, hit_box_factor_x, hit_box_factor_y, cell_size, false);


            if (rightMovement)
                state = "R";
            else
                state = "L";

            character[other1]->jumpState(state, animationClock);

        }

        if (!jumping3) {
            jumping3 = true;
            character[other2]->jump(jumping3, onGround3, gravity, lvl[levelIndex]->getLevel(), Pwidth, hit_box_factor_x, hit_box_factor_y, cell_size, false);

            if (rightMovement)
                state = "R";
            else
                state = "L";

            character[other2]->jumpState(state, animationClock);
            //obj3.jump(jumping3, onGround3, gravity);
        }
    }


    bool leftKey = Keyboard::isKeyPressed(Keyboard::Left);
    bool RightKey = Keyboard::isKeyPressed(Keyboard::Right);
    Tails* t = dynamic_cast<Tails*>(character[1]);


    if (RightKey) {


        //animationClock.restart().asSeconds();
        string state = "R";

        //float next_x = obj.getPosition().x + obj.getVelocity().x;

        // calculating the next position of the player before it goes there
        float next_x = character[main_character_index]->getPosition_x() + character[main_character_index]->getVelocity_x();


        if (character[main_character_index]->noCollision(lvl[levelIndex]->getLevel(), next_x, character[main_character_index]->getPosition_y(), Pwidth, Pheight, hit_box_factor_x, hit_box_factor_y, cell_size)) {

            leftMovement = false;

            if (main_character_index == 1 && character[main_character_index]->getFlightStatus()) {
                t->flyAnimation(state);
            }
            else if (main_character_index == 2 && k->getPunchingStatus()) {
                k->punChing_animation(state);
            }
            else {
                character[main_character_index]->jogState(state, animationClock);
                //character[main_character_index]->movement(ev, character[main_character_index]->getPosition_x(), leftMovement, dt);
                character[other1]->jogState(state, animationClock);
                character[other2]->jogState(state, animationClock);
            }

          

            character[main_character_index]->movement(ev, character[main_character_index]->getPosition_x(), leftMovement, dt);


            //animationClock.restart();
        }

    }

    if (leftKey) {
        //float next_x = obj.getPosition().x - obj.getVelocity().x;
        string state = "L";
        float next_x = character[main_character_index]->getPosition_x() - character[main_character_index]->getVelocity_x();

        if (character[main_character_index]->noCollision(lvl[levelIndex]->getLevel(), next_x, character[main_character_index]->getPosition_y(),
            Pwidth, Pheight,
            hit_box_factor_x, hit_box_factor_y,
            cell_size)) {
            leftMovement = true;

            if (main_character_index == 1 && character[main_character_index]->getFlightStatus()) {
                t->flyAnimation(state);
            }
            else if (main_character_index == 2 && k->getPunchingStatus()) {
                k->punChing_animation(state);
            }
            else {
                character[main_character_index]->jogState(state, animationClock);
                character[other1]->jogState(state, animationClock);
                character[other2]->jogState(state, animationClock);
            }
            character[main_character_index]->movement(ev, character[main_character_index]->getPosition_x(), leftMovement, dt);

        }
    }

    // If no key is pressed still the animation will play if lfyign
   
    // If the player is still moving then applying the decelleration to simulate friction and stuff
    if (!leftKey && !RightKey) {

        // if it encounter a wall infront of it then immediately stops
        if (leftMovement) {
            float next_x = character[main_character_index]->getPosition_x() - character[main_character_index]->getCurrent_x();

            if (!character[main_character_index]->noCollision(lvl[levelIndex]->getLevel(), next_x, character[main_character_index]->getPosition_y(), Pwidth, Pheight, hit_box_factor_x, hit_box_factor_y, cell_size)) {
                character[main_character_index]->setCurrentVelocity();
            }
        }
        else {
            float next_x = character[main_character_index]->getPosition_x() + character[main_character_index]->getCurrent_x();

            if (!character[main_character_index]->noCollision(lvl[levelIndex]->getLevel(), next_x, character[main_character_index]->getPosition_y(), Pwidth, Pheight, hit_box_factor_x, hit_box_factor_y, cell_size)) {
                character[main_character_index]->setCurrentVelocity();
            }
        }

        // If still the velocity is not zero then applying friction
        if (character[main_character_index]->getCurrent_x() != 0) {



            character[main_character_index]->deaccelaration(dt, friction, leftMovement, character[main_character_index]->getPosition_x());


        }

        if (main_character_index == 1 && character[main_character_index]->getFlightStatus()) {
            t->flyAnimation();
        }

    }

    // Making all the other characters to jog before the main player
    
    // if the object collides with the enemy from the botton them momentarity go ahead and set onground = true
    if (bottomCollision) {
        onGround = true;
        jumping = true;
        bottomCollision = false;
        //standClock.restart();
        //bottomCollision = false;
    }

    //if (standClock.getElapsedTime().asSeconds() > 1.5) {
    //   /* onGround = false;*/
    //    jumping = false;1
    //    onGround = false;
    //    bottomCollision = false;
    //}

    if (startofTheGame) {

        /*  Menu will be displayed here */

        // Resetting all the muscis
       /* for (int i = 0; i < 4; i++) {
            lvlMus[levelIndex].stop();
        }*/

        //lvl[levelIndex]->stopMusic(levelIndex);
        
        //lvlMus[levelIndex].setVolume(0);
        cout << "Setting Music of the " << levelIndex << " to zero" << endl;
        lvlMus[levelIndex].stop();

        mainMenu.run(window, startofTheGame, load_save_game);
        //Resetting the clock

        lvlMus[levelIndex].stop();
        lvlMus[levelIndex].play();
        lvlMus[levelIndex].setVolume(30);
        lvl[levelIndex]->setClock();
        score = 0;

        //lvl[levelIndex]->playMusic(levelIndex);
        //lvlMus[levelIndex].setVolume(30);
    }

    // Loading the saves game
    if (load_save_game) {
        loadGame();
        load_save_game = false;
    }


    // Jumping each chractor
    if (jumping) {
        character[main_character_index]->jump(jumping, onGround, gravity, lvl[levelIndex]->getLevel(), Pwidth, hit_box_factor_x, hit_box_factor_y, cell_size, false);

        if (rightMovement)
            state = "R";
        else
            state = "L";

        //character[main_character_index]->jumpState(state, animationClock);
    }

    if (jumping2) {
        character[other1]->jump(jumping2, onGround2, gravity, lvl[levelIndex]->getLevel(), Pwidth, hit_box_factor_x, hit_box_factor_y, cell_size, false);

        if (rightMovement)
            state = "R";
        else
            state = "L";

        //character[other1]->jumpState(state, animationClock);
    }


    if (jumping3) {
        character[other2]->jump(jumping3, onGround3, gravity, lvl[levelIndex]->getLevel(), Pwidth, hit_box_factor_x, hit_box_factor_y, cell_size, false);

        if (rightMovement)
            state = "R";
        else
            state = "L";

        //character[other2]->jumpState(state, animationClock);
    }



    // Applying the ball animations
    if (inFlight) {

        if (rightMovement)
            state = "R";
        else
            state = "L";

        character[main_character_index]->jumpState(state, animationClock);

        character[other1]->jumpState(state, animationClock);

        character[other2]->jumpState(state, animationClock);

    }

    if (!jumping && onGround) {
        inFlight = false;
    }

    //cout << "Flight status " << inFlight << endl;


    // Applying the ability to fly

    if (main_character_index == 1 && character[main_character_index]->isFlying) {
        //Vector2f tmp;

        float tmp_x;
        float tmp_y;

        t->firstFly = false;
        character[main_character_index]->updateFlight(onGround, lvl[levelIndex]->getLevel());
        tmp_x = character[main_character_index]->getPosition_x() - character[main_character_index]->getsprite().getTextureRect().width;
        tmp_y = character[main_character_index]->getPosition_y();
        character[0]->setPosition(tmp_x, tmp_y);
        character[2]->setPosition(tmp_x, tmp_y);
    }

    else {
        for (int i = 0; i < 3; i++) {
            character[i]->isFlying = false;
        }

        // Dynamic casting to get access to tails

        t->firstFly = true;

    }




    // Applying the player's gravity to each player
    if (!jumping) {

        character[main_character_index]->player_gravity(lvl[levelIndex]->getLevel(), offset_y, velocityY, onGround, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, character[main_character_index]->getPosition_x(), character[main_character_index]->getPosition_y(), cell_size, Pheight, Pwidth, onSpring);
    }

    if (!jumping2) {
        character[other1]->player_gravity(lvl[levelIndex]->getLevel(), offset_y, velocityY2, onGround2, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, character[other1]->getPosition_x(), character[other1]->getPosition_y(), cell_size, Pheight, Pwidth, onSpring);

    }

    if (!jumping3) {
        character[other2]->player_gravity(lvl[levelIndex]->getLevel(), offset_y, velocityY3, onGround3, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, character[other2]->getPosition_x(), character[other2]->getPosition_y(), cell_size, Pheight, Pwidth, onSpring);

    }

    

    // Calculating the camera offset which will be used for horizontal scoring
    // Basically calculating each variable at run time for accurate horizontal scrolling
    float screenW = window.getSize().x;
    float screenCenterX = screenW / 2.f;
    float mainWorldX = character[main_character_index]->getPosition_x();
    float cameraOffsetX = mainWorldX - screenCenterX;

    // Checking collisions with the collectible
   /* level.setPlayer(character[main_character_index]);
    level.checkCollision(character[main_character_index]->getsprite(), *character[main_character_index], character[main_character_index]->getAbilityCounter(), cameraOffsetX, bottomCollision);

    if (level.levelUp()) {
        std::cout << "All rings are collected we are ready to level up" << std::endl;
    }*/

    

    //lvl[levelIndex]->setPlayer(character[main_character_index]);

    // Getting the proper jump
    bool isJumping = false;
    bool ground = false;
    switch (main_character_index)
    {
    case 0: isJumping = jumping;
        ground = onGround;
        break;

    case 1: isJumping = jumping2;
        ground = onGround2;
        break;

    case 2:isJumping = jumping3;
        ground = onGround3;
        break;
    default:
        break;
    }

    // Checking the collision of the player with the collectibles and the enemies
    lvl[levelIndex]->checkCollision(character[main_character_index]->getsprite(), *character[main_character_index], character[main_character_index]->getAbilityCounter(), cameraOffsetX, bottomCollision, firstHit, inFlight);

    // Leveling up if all coins are collected
    if (lvl[levelIndex]->levelUp()) {


        lvlMus[levelIndex].setVolume(0);
        std::cout << "Level up" << std::endl;
        if (levelIndex < 4) {

           
            lvl[levelIndex]->setClock();
            levelIndex++;
            if (levelIndex == 4) {
                levelIndex = 0;
                mainMenu.congratsDisplay(window);
                startofTheGame = true;
            }
            else {
                mainMenu.lvlImageDisplay(window);
                lvl[levelIndex]->setClock();
                //lvl[levelIndex]->setClock();
            }
            startOflevel = true;
            lvlMus[levelIndex].setVolume(30);

            reset();
           /* lvl[levelIndex]->reset();
            lvl[levelIndex]->builLevel();*/
        }

    }


    //std::cout << character[main_character_index]->getPosition().x << endl;
    //cout << " Current level Index " << levelIndex << endl;


    // Moving the player toward the mainplayer 
    if (character[other1]->moveTowardMain(character[main_character_index]->getPosition_x(), character[main_character_index]->getPosition_y(), rightMovement)) {
        //Vector2f position = character[other1]->getPosition();

        float position_x = character[other1]->getPosition_x();
        float position_y = character[other1]->getPosition_y();


        if (!rightMovement) {

            position_x += 12;
        }
        else {
            position_x -= 12;

        }

        character[other1]->setPosition(position_x, position_y);
    }

    if (character[other2]->moveTowardMain(character[other1]->getPosition_x(), character[other1]->getPosition_y(), knuckleLeft)) {

        //Vector2f position = character[other2]->getPosition();

        float position_x = character[other2]->getPosition_x();
        float position_y = character[other2]->getPosition_y();

        if (!knuckleLeft)
            position_x += 8;

        else
            position_x -= 8;


        character[other2]->setPosition(position_x, position_y);
    }





    // if the health of the main player get zero then the game is over
    if (character[main_character_index]->gethealth() <= 0) {

        //lvl[levelIndex]->stopMusic(levelIndex);
        lvlMus[levelIndex].setVolume(0);

        mainMenu.gameOverDisplay(window);
        startofTheGame = true;

        reset(lvl);
        lvl[levelIndex]->setClock();
        ringCount = 0;

        //As the game is lost, updating the file
        if(score)
            mainMenu.updateBoard();
        //reset(level);
      
        
    }

    // Checking if all the players
    if (GameOver(character[main_character_index]->getPosition_y(), startofTheGame, lvl[levelIndex]->getElapsedTime(), lvl)) {
        mainMenu.gameOverDisplay(window);

        //reset(level);
        //lvl[levelIndex]->stopMusic(levelIndex);
        lvlMus[levelIndex].setVolume(0);

        std::cout << "game over " << std::endl;
        reset(lvl);
        lvl[levelIndex]->setClock();
        if(score)
            mainMenu.updateBoard();

        startOflevel = true;
        startofTheGame = true;
        
    }




    // Updating all the data to the highlights
    //ringCount += lvl[levelIndex]->ringCollectCount();
    //if(score)
        highlight->upDateBoard(score, lvl[levelIndex]->getElapsedTime(), lvl[levelIndex]->ringCollectCount(), character[main_character_index]->gethealth());
    //std::cout << "Special Ability counter : " << character[main_character_index]->SpecialAbilityCounter << std::endl;


    //std::cout << "Health of the player of : " << main_character_index << ' ' << character[main_character_index]->gethealth() << std::endl;

    //std::cout << "Time elapsed in the level : " << levelIndex + 1 << " is : " << lvl[levelIndex]->getElapsedTime() << std::endl;

    //cout << "Player he
    // 
    // alth Clock : " << character[main_character_index]->healthClock.getElapsedTime().asSeconds() << endl;
    

    if (levelIndex == 3) // Boss level
    {
        lvl[levelIndex]->removeWall();
    }
    

    character[main_character_index]->setDamageStatus();
    //cout << "Player damage status : " << character[main_character_index]->noDamage << endl;
    //cout << dt << endl;

    // Saving the game
    if (save_game) {
        character[main_character_index]->truncateFile();
        character[main_character_index]->saveGame(character[main_character_index]->getPosition_x(), character[main_character_index]->getPosition_y(), character[main_character_index]->gethealth());
        character[other1]->saveGame(character[other1]->getPosition_x(), character[other1]->getPosition_y(), character[other1]->gethealth());
        character[other2]->saveGame(character[other2]->getPosition_x(), character[other2]->getPosition_y(), character[other2]->gethealth());

        lvl[levelIndex]->saveLevel(levelIndex);

        save_game = false;
    }

    //cout << levelIndex << endl;

}

//void Game::render()
//{
//    window.clear();
//
//    level.display_level(window);
//    //display_level(window, height, width, lvl, wallSprite1, cell_size);
//    //obj.draw_player(window, obj.getsprite(), obj.getPosition().x, obj.getPosition().y);
//
//    character[main_character_index]->draw_player(window, character[main_character_index]->getsprite(), character[main_character_index]->getPosition().x, character[main_character_index]->getPosition().y);
//
//    //cout << character[main_character_index]->getPosition().x << '\t' << character[main_character_index]->getPosition().y << endl;
//
//    if (character[other1]->PositionCheck(character[main_character_index]->getPosition())) {
//
//        Vector2f newPostion = character[main_character_index]->getPosition();
//        newPostion.x -= 200;
//        newPostion.y -= 100;
//        character[other1]->setPosition(newPostion);
//
//    }
//
//    if (character[other2]->PositionCheck(character[other1]->getPosition())) {
//
//        Vector2f newPostion = character[other1]->getPosition();
//        newPostion.x -= 200;
//        newPostion.y -= 100;
//        character[other2]->setPosition(newPostion);
//
//    }
//
//    
//
//
//    /*character[other1]->draw_player(window, character[other1]->getsprite(), character[other1]->getPosition().x, character[other1]->getPosition().y);
//    character[other2]->draw_player(window, character[other2]->getsprite(), character[other2]->getPosition().x, character[other2]->getPosition().y);*/
//
//    //float dt = frameClock.getElapsedTime().asSeconds();
//    //obj1.follow(obj.getPosition(), 12, 0.5);
//
//    //characters[0]->draw_player(window, characters[0]->getsprite(), characters[0]->getPosition().x, characters[0]->getPosition().y);
//
//    //Updating the view
//    //v.setCenter(obj.getPosition());
//   /* v.setCenter(character[main_character_index]->getPosition());
//    window.setView(v);*/
//
//    window.display();
//}
//
//
//



void Game::render()
{
    window.clear();

   // Computing the camera offset
    float screenW = window.getSize().x;
    float screenCenterX = screenW / 2.f;
    float mainWorldX = character[main_character_index]->getPosition_x();
    float cameraOffsetX = mainWorldX - screenCenterX;

    

    // Displaying the level
    lvl[levelIndex]->display_level(window, cameraOffsetX, character[main_character_index]->getsprite(), levelIndex);



    // respawning the charcter if they get too far from the main charactder
    if (character[other1]->PositionCheck(character[main_character_index]->getPosition_x(), character[main_character_index]->getPosition_y())) {

        //Vector2f newPostion = character[main_character_index]->getPosition();
        float newPostion_x = character[main_character_index]->getPosition_x();
        float newPostion_y = character[main_character_index]->getPosition_y();

        newPostion_x -= 200;
        newPostion_y -= 100;
        character[other1]->setPosition(newPostion_x, newPostion_y);

    }

    if (character[other2]->PositionCheck(character[other1]->getPosition_x(), character[other1]->getPosition_y())) {

        //Vector2f newPostion = character[other1]->getPosition();

        float newPostion_x = character[main_character_index]->getPosition_x();
        float newPostion_y = character[main_character_index]->getPosition_y();

        newPostion_x -= 200;
        newPostion_y -= 100;
        character[other2]->setPosition(newPostion_x, newPostion_y);

    }

    /// Drawing the players
    character[other1]->draw_player(window, character[other1]->getsprite(), character[other1]->getPosition_x(), character[other1]->getPosition_y(), cameraOffsetX, false);
    character[other2]->draw_player(window, character[other2]->getsprite(), character[other2]->getPosition_x(), character[other2]->getPosition_y(), cameraOffsetX, false);


    character[main_character_index]->draw_player( window, character[main_character_index]->getsprite(), character[main_character_index]->getPosition_x(), character[main_character_index]->getPosition_y(),  cameraOffsetX,
        true
    );

    // rendering the scoreboard 
    highlight->render(window);

    window.display();
}




