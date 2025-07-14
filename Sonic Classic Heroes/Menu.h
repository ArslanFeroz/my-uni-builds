#pragma once
#include"SFML/Window.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"

#include <fstream>
#include<iostream>

using namespace std;
using namespace sf;

class Menu
{

	Text* pausMenu;


	Text nameWindow;
	Text optionText[3];
	Text menuText[5];
	Font menuFont;


	Music menuMusic;
	Music gameOver;
	Music win;

	int selected = 0;
	Color selectedCol;
	Color nonSelectedCol;

	Texture menuTex;
	Sprite menuSprite;

	const int TotalMenu = 5;
	const int Totaloption = 3;
	const int TotalPause = 3;
	const int max_records = 10;

	std::string fileAddress;
	std::string* name;
	int* score;

	Text* leaderBoardText;
	Text* nameText;
	Text* scoreText;

	Sprite* lvlImg;
	Texture* lvlImg_tex;
	Sprite* congrats;
	Texture* congrats_tex;
	Sprite* game_over;
	Texture* game_over_tex;

	Texture* menu_bg_tex;
	Sprite* menu_bg_sprite;

	Music buttonMusic;

	Clock clock;

	const float maxTime = 5.f;


	

	void runMusic(bool& startOfgame);
	void setFont(Text* obj, int size);
	void setFont(string* Name, int* Scoring);
	void options(RenderWindow& window);
	void enterNameScreen(RenderWindow& window);
	void leaderBoard(RenderWindow& window);
	
	//void setMusic(Event& ev);

public:
	Menu();
	~Menu();
	void PauseMenu(RenderWindow& window, bool& startOfgame, bool& saveGame);
	void setScore(int* score);
	void updateBoard();
	void run(RenderWindow& window, bool& startOfgame, bool& loadSveGame);
	void lvlImageDisplay(RenderWindow& window);
	void congratsDisplay(RenderWindow& window);
	void gameOverDisplay(RenderWindow& window);
};

