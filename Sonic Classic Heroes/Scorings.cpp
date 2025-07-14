#include "Scorings.h"

Scorings::Scorings()
{
	text = new Text[4];
	font = new Font;
	fontAddress = "Data/textFont.otf";
	
	if (!font->loadFromFile(fontAddress))
		cout << "Error loading the font" << endl;

	totalScores = 0;
	ringCount = 0;
	timeLeft = 0;
	health = 0;

	str = new string[4];
	str[0] = "Scores : ";
	str[1] = "Time left : ";
	str[2] = "Ring Count : ";
	str[3] = "Health : ";

	position_x = 50.f;
	position_y = 50.f;

	// Initialyzing the text

	for (int i = 0; i < 4; i++) {
		text[i].setCharacterSize(24);
		text[i].setFillColor(Color::White);
		text[i].setFont(*font);
		text[i].setPosition(position_x, (i * 25) + position_y);
	}

	text[0].setString(str[0] + std::to_string(totalScores));
	text[1].setString(str[1] + std::to_string(timeLeft));
	text[2].setString(str[2] + std::to_string(ringCount));
	text[3].setString(str[3] + std::to_string(health));


	// Positioning
}

Scorings::~Scorings()
{
	delete[]text;
	delete[]str;
}

void Scorings::upDateBoard(int& totalScores, float& timeLeft, int& ringCount, int health)
{
	this->totalScores = totalScores;
	this->timeLeft = timeLeft;
	this->ringCount = ringCount;
	this->health = health;
}

void Scorings::render(RenderWindow& window)
{
	// First setting all the fonts
	text[0].setString(str[0] + std::to_string(totalScores));
	text[1].setString(str[1] + std::to_string(timeLeft));
	text[2].setString(str[2] + std::to_string(ringCount));
	text[3].setString(str[3] + std::to_string(health));


	for (int i = 0; i < 4; i++) {
		window.draw(text[i]);
	}
}

