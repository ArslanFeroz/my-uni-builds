#include "extra_life.h"

extra_life::extra_life()
{
	bool b = false;
	setStatus(b);
	address = "Data/health_sprite.png";
}

void extra_life::setAttributes(std::string& a, float& x, float& y)
{
	setData(a, height, width, x, y);
}

void extra_life::CollectibleAnimation()
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
