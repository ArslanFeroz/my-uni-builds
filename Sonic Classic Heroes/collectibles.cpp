#include "collectibles.h"
#include<iostream>
collectibles::collectibles()
{
	sprite = NULL;
	spriteSheet = NULL;
}



collectibles::~collectibles()
{
	delete sprite;
	delete spriteSheet;
}

Vector2f collectibles::getPosition()
{
	return position;
}

bool collectibles::getPresentStatus()
{
	return presentStatus;
}

void collectibles::setPosition(Vector2f& position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

void collectibles::setPosition(float& x, float& y)
{
	position.x = x;
	position.y = y;
}

bool collectibles::collision(Sprite& obj, float cameraOffset)
{

	
	if (!presentStatus)
		return false;

	// player AABB in world space
	float player_x = obj.getPosition().x;
	float player_y = obj.getPosition().y;
	float player_width = static_cast<float>(obj.getTextureRect().width);
	float player_height = static_cast<float>(obj.getTextureRect().height);

	// collectible AABB in world space
	float collectible_x = position.x;
	float collectible_y = position.y;
	float collectible_width = static_cast<float>(width) * sprite->getScale().x - 5;
	float collectible_height = static_cast<float>(height) * sprite->getScale().y - 5;

	// overlap test
	bool overlap =
		(player_x + player_width > collectible_x) &&
		(player_x < collectible_x + collectible_width) &&
		(player_y + player_height > collectible_y) &&
		(player_y < collectible_y + collectible_height);

	if (overlap) {
		presentStatus = false;
		return true;
	}
	return false;

	

}

void collectibles::setStatus(bool& b)
{
	presentStatus = b;
}

void collectibles::setData(std::string& ad, int h, int w, float& x, float& y)
{
	address = ad;
	height = h;
	width = w;

	sprite = new Sprite;
	spriteSheet = new Texture;
	spriteSheet->loadFromFile(address);

	sprite->setTexture(*spriteSheet);
	sprite->setTextureRect(IntRect(0, 0, w, h));
	sprite->setScale(3, 3);
	position.x = x;
	position.y = y;

	sprite->setPosition(position);

	presentStatus = true;
}


void collectibles::render(RenderWindow& window, float cameraOffset)
{
	sprite->setPosition(position.x - cameraOffset, position.y);
	window.draw(*sprite);
	//window.display();
}


