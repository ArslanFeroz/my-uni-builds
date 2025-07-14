#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "iostream"


using namespace std;
using namespace sf;

class Scorings
{

	Text* text;
	Font* font;
	string* str;

	string fontAddress;

	float scale_x;
	float scale_y;

	float position_x;
	float position_y;


	int totalScores;
	float timeLeft;
	int ringCount;
	int health;


public:
	Scorings();
	~Scorings();

	void upDateBoard(int& totalScores, float& timeLeft, int& ringCount, int health);
	void render(RenderWindow& window);
	
};

