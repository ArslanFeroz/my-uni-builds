#include "power_ups.h"

power_ups::power_ups()
{
	bool b = false;
	setStatus(b);
	address = "Data/extraLife.png";
}

void power_ups::setAttributes(std::string& a, float& x, float& y)
{
	setData(a, height, width, x, y);

}

void power_ups::CollectibleAnimation()
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
