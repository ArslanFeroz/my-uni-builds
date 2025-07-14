

//#pragma once
//#include <iostream>
//#include <fstream>
//#include <cmath>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Window.hpp>
//
////#include "Player.h"
//#include"levels.h"
//#include"Menu.h"
//
//
//
//
////#include"soni"
//#include"Player.h"
//
//#include "Sonic.h"
//
////#include"tails.h"
//
//using namespace sf;
//using namespace std;
//
//
//class game {
//
//    RenderWindow window;
//    Event ev;
//    int screen_x = 1200, screen_y = 900;
//    const int cell_size;
//    float gravity, terminal_Velocity;
//    float scale_x, scale_y;
//    int raw_img_x, raw_img_y;
//    int Pheight, Pwidth;
//    int hit_box_factor_x, hit_box_factor_y;
//
//    Music lvlMus;
//    View v;
//    Clock animationClock;
//
//    float offset_y = 0;
//    float velocityY = 0;
//    bool onGround = false;
//    bool jumping;
//    bool leftMovement;
//    bool startofTheGame;
//
//
//    Sonic obj;
//
//    //Tails obj1;
//    level1 level;
//    Menu mainMenu;
//
//    //player** characters;
//
//
//public:
//
//    // construcor
//    game() : window(VideoMode(1200, 900), "Sonic the Hedgehog-OOP", Style::Close), cell_size(64)
//        , gravity(1.f)
//        , terminal_Velocity(20.f)
//        , scale_x(2.5f)
//        , scale_y(2.5f)
//        , raw_img_x(24)
//        , raw_img_y(35)
//    {
//        window.setVerticalSyncEnabled(true);
//        window.setFramerateLimit(60);
//
//        // Load level music
//        lvlMus.openFromFile("Data/labrynth.ogg");
//        lvlMus.setVolume(30);
//        lvlMus.setLoop(true);
//        lvlMus.play();
//
//        // Calculate player hitbox dimensions
//        Pheight = raw_img_y * scale_y;
//        Pwidth = raw_img_x * scale_x;
//        hit_box_factor_x = int(8 * scale_x);
//        hit_box_factor_y = int(5 * scale_y);
//
//        // Center view on player
//        v.setSize(screen_x, screen_y);
//        v.setCenter(obj.getPosition());
//
//        // Initialize state
//        startofTheGame = true;
//        jumping = false;
//        leftMovement = false;
//
//
//        // test
//        /*characters = new player * [3];
//
//        characters[0] = new sonic;
//        characters[1] = new Tails;
//        characters[2] = new knuckles;*/
//
//        animationClock.restart();
//    }
//
//
//
//    // Main gameloop
//
//    void run() {
//        while (window.isOpen()) {
//            update();
//            render();
//        }
//    }
//
//    // Processing some basic events like close still state 
//
//
//    // Updating the window
//    void update() {
//        if (onGround)
//            jumping = false;
//
//        while (window.pollEvent(ev))
//        {
//            if (ev.type == Event::Closed)
//            {
//                window.close();
//            }
//
//            if (ev.type == Event::KeyReleased) {
//                // Changing the state of the sprite
//                obj.Still_State(ev);
//            }
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Space)) {
//            if (!jumping) {
//
//                /*We will call the jump function over here*/
//
//                jumping = true;
//                obj.jump(jumping, onGround, gravity);
//
//            }
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Escape))
//        {
//            window.close();
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Right)) {
//
//
//            //animationClock.restart().asSeconds();
//            string state = "R";
//
//            float next_x = obj.getPosition().x + obj.getVelocity().x;
//
//
//            if (obj.noCollision(level.getLevel(), next_x, obj.getPosition().y, Pwidth, Pheight, hit_box_factor_x, hit_box_factor_y, cell_size)) {
//                leftMovement = false;
//
//
//                obj.jogState(state, animationClock);
//                obj.movement(ev, obj.getPosition().x, leftMovement);
//            }
//
//
//            //animationClock.restart();
//
//
//            /*  We will call the movement function over here*/
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Left)) {
//            //float next_x = obj.getPosition().x - obj.getVelocity().x;
//            string state = "L";
//            float next_x = obj.getPosition().x - obj.getVelocity().x;
//
//            if (obj.noCollision(level.getLevel(), next_x, obj.getPosition().y,
//                Pwidth, Pheight,
//                hit_box_factor_x, hit_box_factor_y,
//                cell_size)) {
//                leftMovement = true;
//
//                //-obj.movement(ev, obj.getPosition().x, leftMovement);
//                            // animate the left jog exactly as you do for right
//                obj.jogState(state, animationClock);
//                obj.movement(ev, obj.getPosition().x, leftMovement);
//            }
//        }
//
//        if (startofTheGame) {
//
//            /*  Menu will be displayed here */
//
//            mainMenu.run(window, startofTheGame);
//        }
//
//        if (jumping) {
//            obj.jump(jumping, onGround, gravity);
//        }
//
//
//
//        if (!jumping) {
//            obj.player_gravity(level.getLevel(), offset_y, velocityY, onGround, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, obj.getPosition().x, obj.getPosition().y, cell_size, Pheight, Pwidth);
//        }
//
//
//
//
//    }
//
//
//
//    void render() {
//        window.clear();
//
//        level.display_level(window);
//        //display_level(window, height, width, lvl, wallSprite1, cell_size);
//        obj.draw_player(window, obj.getsprite(), obj.getPosition().x, obj.getPosition().y);
//        //obj1.draw_player(window, obj1.getsprite(), obj1.getPosition().x, obj1.getPosition().y);
//
//        //characters[0]->draw_player(window, characters[0]->getsprite(), characters[0]->getPosition().x, characters[0]->getPosition().y);
//
//        //Updating the view
//        v.setCenter(obj.getPosition());
//        //v.setCenter(characters[0]->getPosition());
//        window.setView(v);
//
//        window.display();
//
//    }
//
//
//
//    // Destructir
//   /* virtual ~game() {
//        for (int i = 0; i < 3; i++) {
//            delete characters[i];
//        }
//        delete[]characters;
//    }*/
//};
//

//#pragma once
//#include"SFML/Window.hpp"
//#include"SFML/Graphics.hpp"
//
//using namespace sf;
//
//class menu {
//	Texture menuTex;
//	Sprite menuSprite;
//
//public:
//
//	//Constructor
//	menu() {
//		menuTex.loadFromFile("Data/Menu.png");
//		menuSprite.setTexture(menuTex);
//		//menuSprite.setScale(2, 2);
//	}
//
//
//	//Update
//
//	//Render
//	void run(RenderWindow& window, bool& startOfgame) {
//		startOfgame = false;
//		while (window.isOpen()) {
//
//			Event ev;
//			while (window.pollEvent(ev)) {
//				if (ev.type == Event::KeyPressed) {
//					if (ev.key.code == Keyboard::S) {
//						//Extiting the menu loop
//						return;
//					}
//					else if (ev.key.code == Keyboard::E) {
//						window.close();
//					}
//				}
//			}
//
//			window.clear();
//			window.draw(menuSprite);
//			window.display();
//		}
//	}
//
//	
//
//
//
//
//
//};
//#pragma once
//#include "SFML/Window.hpp"
//#include "SFML/Graphics.hpp"
//
//using namespace sf;
//
//// Base class
//class player {
//
//	Sprite sprite;
//	Vector2f scale;
//	Vector2f velocity;
//	Vector2f position;
//
//
//	Texture rightStill;
//
//	Texture leftStill;
//
//	Texture rightMotion;
//	Texture leftMotion;
//
//
//	// boolean to determine the main character, which obviosly at start will be sonic
//	bool main;
//
//
//public:
//	player() {
//		scale.x = 2.5;
//		scale.y = 2.5;
//
//		velocity.x = 10;
//		velocity.y = -20; // initial jump velocity;
//
//		main = false;
//
//
//	}
//
//	player(Vector2f& pos) {
//		scale.x = 2.5;
//		scale.y = 2.5;
//
//		velocity.x = 10;
//		velocity.y = -20; // initial jump velocity;
//
//
//		position = pos;
//
//	}
//
//
//	//Common member functions
//
//	void setTexture(std::string& address, std::string& address2, std::string& address3, std::string& address4) {
//		rightStill.loadFromFile(address);
//		sprite.setTexture(rightStill);
//		sprite.setScale(scale);
//		sprite.setPosition(position);
//
//		// additonal texture
//		leftStill.loadFromFile(address2);
//		leftMotion.loadFromFile(address3);
//		rightMotion.loadFromFile(address4);
//	}
//
//	void jump(bool& jumping, bool& onground, float gravity) {
//		if (onground) {
//			velocity.y = -20; // initial jump speed
//			onground = false;
//			jumping = true;
//		}
//
//		// simulate one frame of upward motion
//		if (jumping) {
//			position.y += velocity.y;     // move up
//			velocity.y += gravity;        // gravity starts pulling down
//
//			if (velocity.y >= 0) {        // reached top of jump
//				jumping = false;
//			}
//
//			sprite.setPosition(position);
//		}
//	}
//
//
//
//	void movement(Event& ev, float& player_x, bool& leftMovement) {
//		if (leftMovement) {
//
//			player_x -= velocity.x;
//
//		}
//		else {
//			player_x += velocity.x;
//		}
//	}
//
//	bool noCollision(char** lvl, float player_x, float player_y, int Pwidth, int Pheight, int hit_box_factor_x, int hit_box_factor_y, const int cell_size) {
//
//		char left_mid = lvl[
//			(int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size
//		][
//			(int)(player_x + hit_box_factor_x) / cell_size
//		];
//
//		char right_mid = lvl[
//			(int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size
//		][
//			(int)(player_x + hit_box_factor_x + Pwidth) / cell_size
//		];
//
//		if ((left_mid == 'w' || right_mid == 'w') || (left_mid == 'q' || right_mid == 'q') || (left_mid == 'b' || right_mid == 'b')
//			) {
//			return false;
//		}
//
//
//		return true;
//	}
//
//	void Still_State(Event& ev) {
//		if (ev.key.code == Keyboard::Right) {
//			sprite.setTexture(rightStill);
//			sprite.setTextureRect(IntRect(0, 0, 40, 40));
//		}
//
//
//		if (ev.key.code == Keyboard::Left) {
//			sprite.setTexture(leftStill);
//			sprite.setTextureRect(IntRect(0, 0, 40, 40));
//
//		}
//
//	}
//
//	void jogState(std::string& state, Clock& clock) {
//
//		static int currentFrame = 0;
//		const float switchTime = 0.1f;
//		const int width = 40;
//		const int height = 40;
//		const int frameCount = 10;
//
//		// only restart the clock when we actually advance the frame!
//		if (clock.getElapsedTime().asSeconds() > switchTime) {
//			currentFrame++;
//			if (currentFrame >= frameCount)
//				currentFrame = 0;
//			clock.restart();
//		}
//
//		// compare to the string literal "R" / "L", not the character 'R'
//		if (state == "R") {
//			sprite.setTexture(rightMotion);
//			sprite.setTextureRect(IntRect(currentFrame * width, 0, width, height));
//		}
//		else if (state == "L") {
//			sprite.setTexture(leftMotion);
//			sprite.setTextureRect(IntRect(currentFrame * width, 0, width, height));
//		}
//	}
//
//	// Gravity
//	void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth)
//	{
//		offset_y = player_y;
//
//		offset_y += velocityY;
//
//		char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x) / cell_size];
//		char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth) / cell_size];
//		char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size];
//
//
//
//		if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w')
//			|| (bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q')
//			|| (bottom_left_down == 'b' || bottom_mid_down == 'b' || bottom_right_down == 'b'))
//		{
//			onGround = true;
//		}
//		else
//		{
//			player_y = offset_y;
//			onGround = false;
//		}
//
//		if (!onGround)
//		{
//			velocityY += gravity;
//			if (velocityY >= terminal_Velocity) velocityY = terminal_Velocity;
//		}
//
//		else
//		{
//			velocityY = 0;
//		}
//
//		position.y = player_y;                 // synchronize your class position
//		sprite.setPosition(position);
//
//	}
//
//	//void follow(const Vector2f& targetPos, float speed, float dt) {
//	//	// Compute direction vector
//	//	Vector2f dir = targetPos - position;
//	//	float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//	//	if (len > 0.f) {
//	//		// Normalize
//	//		dir /= len;
//	//		// Move toward the target
//	//		position += dir * speed * dt;
//	//		// Update sprite position
//	//		sprite.setPosition(position);
//	//	}
//	//}
//
//	// function to determing who is the current leader sprite to we may 
//
//
//
//	// rendering
//	void draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y) {
//
//		LstillSprite.setPosition(player_x, player_y);
//		window.draw(LstillSprite);
//
//	}
//
//	//Setters and getters
//	Sprite& getsprite() {
//		return sprite;
//	}
//	Vector2f& getPosition() {
//		return position;
//	}
//
//	Vector2f getVelocity() {
//		return velocity;
//	}
//
//	bool getStatus() { return main; }
//
//	void setSpeed(float& x, float& y) {
//		velocity.x = x;
//		velocity.y = y;
//	}
//
//	void setPosition(Vector2f& pos) {
//		position = pos;
//	}
//
//	void setStatus(bool& s) {
//		main = s;
//	}
//
//	/*void setleftJog(bool& state) {
//		leftJog = state;
//	}
//	void righJog(bool& state) {
//		rightJog = state;
//	}*/
//
//
//};
//
//

//

//


//class Tails :public player {
//	std::string leftStill;
//	std::string rightStill;
//	std::string leftMotion;
//	std::string rightMotion;
//
//	Vector2f position;
//
//public:
//	Tails() :player() {
//
//		rightStill = "Data/tails_right.png";
//		leftStill = "Data/tails_left.png";
//		leftMotion = "Data/tail_left_jog.png";
//		rightMotion = "Data/tail_right_jog.png";
//
//		float vx = 10;
//		float vy = -20;
//
//		setTexture(rightStill, leftStill, leftMotion, rightMotion);
//		setSpeed(vx, vy);
//
//		position.x = 150 - getsprite().getTextureRect().width - 5;
//		position.y = 100;
//
//		setPosition(position);
//
//		bool state = false;
//		setStatus(state);
//
//	}
//
//
//	void flight() {
//
//		// we will define it latere
//	}
//
//};
//

//class knuckles : public player {
//
//	std::string leftStill;
//	std::string rightStill;
//	std::string leftMotion;
//	std::string rightMotion;
//
//	Vector2f position;
//
//
//public:
//
//	knuckles() :player() {
//
//		rightStill = "Data/knuckles_leftStill.png";
//		leftStill = "Data/knuckles_rightStill.png";
//		leftMotion = "Data/tail_left_jog.png";
//		rightMotion = "Data/tail_right_jog.png";
//
//		float vx = 12;
//		float vy = -20;
//
//		setTexture(rightStill, leftStill, leftMotion, rightMotion);
//		setSpeed(vx, vy);
//
//		position.x = 300 - getsprite().getTextureRect().width - 5;
//		position.y = 100;
//
//		setPosition(position);
//
//		bool state = false;
//		setStatus(state);
//	}
//
//};
//
//




//class sonic : public player {
//	std::string leftStill;
//	std::string rightStill;
//	std::string leftMotion;
//	std::string rightMotion;
//
//	Vector2f position;
//
//public:
//	sonic() : player() {
//		rightStill = "Data/0right_still.png";
//		leftStill = "Data/0left_still.png";
//		leftMotion = "Data/0jog_left.png";
//		rightMotion = "Data/0jog_right.png";
//
//		float vx = 18;
//		float vy = -20;
//
//
//		setTexture(rightStill, leftStill, leftMotion, rightMotion);
//		setSpeed(vx, vy);
//
//		position.x = 200;
//		position.y = 100;
//
//		setPosition(position);
//
//		//Initially setting sonic as the main character
//		bool state = true;
//		setStatus(state);
//
//	}
//};

#include "Game.h"

int main() {
	Game obj;
	obj.run();
}
