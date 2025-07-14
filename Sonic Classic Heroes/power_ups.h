#pragma once
#include"collectibles.h"
class power_ups:public collectibles
{
private:
	const int width = 16;
	const int height = 16;
	std::string address;

	const int totalFrames = 4;
	const float switchTime = 0.2;
	int currentFrame = 0;
public:

	power_ups();
	//rings(std:: string& a);

	void setAttributes(std::string& a, float& x, float& y);
	void CollectibleAnimation();
};

