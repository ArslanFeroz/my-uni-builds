#include "level1.h"
#include <iostream>

level1::level1()
{


	height = 14;
	width = 200;
	address = "Data/level1.txt";
	totalRings = 50;
	totalLives = 5;
	totalPowerUps = 2;
	totalBrains = 5;
	totalBeeBots = 5;
	totalBugs = 5;
	totalCrabs = 5;

	std::cout << "Constructor of level 1 is called." << std::endl;

	maxTime = 70;

	setAttributes(address, height, width, totalRings, totalLives, totalPowerUps, totalBrains, totalBeeBots, totalBugs, totalCrabs, 0);
}
