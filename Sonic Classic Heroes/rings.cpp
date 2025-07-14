#include "rings.h"
#include<iostream>
rings::rings()
{
	bool b = false;
	setStatus(b);
	address = "Data/ring.png";
}
//rings::rings(std::string& a) : collectibles(a, height, width) {}

void rings::setAttributes(std::string& a, float& x, float& y)
{
	setData(a, height, width, x, y);
}

void rings::CollectibleAnimation()
{
	if (clock.getElapsedTime().asSeconds() > switchTime) {
		currentFrame++;
		if (currentFrame >= totalFrames) {
			currentFrame = 0;
		}
		clock.restart();

	}

	//Setting the texture rect;
	sprite->setTextureRect(IntRect(currentFrame * width, 0, width, height));
}

