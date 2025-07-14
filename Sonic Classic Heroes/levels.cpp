#pragma once

#include "levels.h"

void levels::saveLevel(int& levelIndex)
{

	// Saving all data to the files
	fstream myfile;
	myfile.open("Data/data.txt", ios::app);

	while (myfile.is_open()) {

		//  saving all the present status of the rings and enemies
		for (int i = 0; i < BrainCounter; i++) {
			myfile << brain[i]->getStatus();
		}

		myfile << '\n';

		for (int i = 0; i < BeeCounter; i++) {
			myfile << bee[i]->getStatus();
		}

		myfile << '\n';

		for (int i = 0; i < bugCounter; i++) {
			myfile << bug[i]->getStatus();
		}

		myfile << '\n';

		for (int i = 0; i < crabCounter; i++) {
			myfile << crab[i]->getStatus();
		}

		myfile << '\n';

		for (int i = 0; i < ringCounter; i++) {
			myfile << rng[i]->getPresentStatus();
		}

		myfile << '\n';

		// saving levels index, score and ring count
		myfile << levelIndex;
		myfile << '\n';
		myfile << *score;
		myfile << '\n';

		myfile << ringCollectedCount;

		myfile.close();
	}

}

void levels::loadEnemyStatuses(string sBrain, string sBee, string sBug, string sCrab, string sRing, int ringCount)
{
	// loading all the data from the file which was opened in the game class
	for (int i = 0; i < BrainCounter; i++) {
		bool status;
		if (sBrain[i] == '1')
			status = true;
		else
			status = false;
		brain[i]->setStatus(status);
	}

	for (int i = 0; i < BeeCounter; i++) {
		bool status;
		if (sBee[i] == '1')
			status = true;
		else
			status = false;
		bee[i]->setStatus(status);
	}

	for (int i = 0; i < bugCounter; i++) {
		bool status;
		if (sBug[i] == '1')
			status = true;
		else
			status = false;
		bug[i]->setStatus(status);
	}

	for (int i = 0; i < crabCounter; i++) {
		bool status;
		if (sCrab[i] == '1')
			status = true;
		else
			status = false;
		crab[i]->setStatus(status);
	}

	for (int i = 0; i < ringCounter; i++) {
		bool status;
		if (sRing[i] == '1')
			status = true;
		else
			status = false;
		rng[i]->setStatus(status);
	}

	ringCollectedCount = ringCount;
}

void levels::springAnimation()
{
	// Animating the spring sprite
	if (springClock.getElapsedTime().asSeconds() > 0.3) {
		spring_cFrame++;
		if (spring_cFrame > spring_tFrame)
			spring_cFrame = 0;
		springClock.restart();
	}

	springs->setTextureRect(IntRect(spring_cFrame * spring_width, 0, spring_width, spring_height));
}

void levels::setAttributes(std::string& fileAddress, int height, int width, int totalRings, int totalLives, int totalPowerups, int totalBrains, int totalBeebots, int totalBugs, int totalCrab, int eggStingerCount)
{
	address = fileAddress;
	this->height = height;
	this->width = width;
	this->Total_rings = totalRings;
	this->Total_lives = totalLives;
	this->Total_powers = totalPowerups;
	this->Total_brain = totalBrains;
	this->Total_bee = totalBeebots;
	this->Total_bugs = totalBugs;
	this->Total_crabs = totalCrab;
	this->Total_eggStingers = eggStingerCount;


	wall1 = new Sprite;
	wall2 = new Sprite;
	wall3 = new Sprite;
	spikes = new Sprite;
	springs = new Sprite;
	crystals = new Sprite;

	wall1->setTexture(wall1_tex);
	wall2->setTexture(wall2_tex);
	wall3->setTexture(wall3_tex);

	/*wall1->setScale(scale);
	wall2->setScale(scale);
	wall3->setScale(scale);*/

	spikes->setTexture(spike_tex);
	crystals->setTexture(crystal_tex);
	springs->setTexture(spring_tex);
	springs->setTextureRect(IntRect(0, 0, spring_width, spring_height));
	//spikes->setScale(scale);

	lvl = new char* [height];
	for (int i = 0;i < height; i++) {
		lvl[i] = new char[width];
	}

	//Making the rngs
	rng = new rings * [Total_rings];
	for (int i = 0; i < Total_rings; i++) {
		rng[i] = nullptr;
	}

	//making the lives
	life = new extra_life * [Total_lives];
	for (int i = 0; i < Total_lives; i++) {
		life[i] = nullptr;
	}

	//making the power ups
	powers = new power_ups * [Total_powers];
	for (int i = 0; i < Total_powers; i++) {
		powers[i] = nullptr;
	}

	//Making the enemies
	// Bat brains
	brain = new Bat_Brain * [Total_brain];
	for (int i = 0; i < Total_brain; i++) {
		brain[i] = nullptr;
	}

	// Bee bots
	bee = new Bee_bot * [Total_bee];
	for (int i = 0; i < Total_bee; i++) {
		bee[i] = nullptr;
	}

	// Moto bugs
	bug = new moto_bug * [Total_bugs];
	for (int i = 0; i < Total_bugs; i++) {
		bug[i] = nullptr;
	}

	// Crab meats
	crab = new crabMeat * [Total_crabs];
	for (int i = 0; i < Total_crabs; i++) {
		crab[i] = nullptr;
	}

	//Egg stingers
	egg = new eggStinger * [Total_eggStingers];
	for (int i = 0; i < Total_eggStingers; i++) {
		egg[i] = nullptr;
	}


	// Using flaot arrays to store the initial positions of all the enemies, whcih will be used in the level reset functiosn
	//
	brainPositions_x = new float[Total_brain];
	brainPositions_y = new float[Total_brain];

	beePositions_x = new float[Total_bee];
	beePositions_y = new float[Total_bee];

	bugPositions_x = new float[Total_bugs];
	bugPositions_y = new float[Total_bugs];

	crabPositions_x = new float[Total_crabs];
	crabPositions_y = new float[Total_crabs];

	eggPositions_x = new float[Total_eggStingers];
	eggPositions_y = new float[Total_eggStingers];


	/*brainPositions = new Vector2f[Total_brain];
	beePositions = new Vector2f[Total_bee];
	bugPositions = new Vector2f[Total_bugs];
	crabPositions = new Vector2f[Total_crabs];
	eggPositions = new Vector2f[Total_eggStingers];*/


	// building the level
	builLevel();
}

bool levels::levelUp()
{
	return ringCollectedCount == ringCounter;
}

// COnstructor
levels::levels()
{

	
	//ob = o;
	elapsedTime = 0;
	score = nullptr;

	cell_Size = 64;
	scale.x = 2.5;
	scale.y = 2.5;

	ringCounter = 0;
	lifeCounter = 0;
	powerCounter = 0;

	BeeCounter = 0;
	BrainCounter = 0;
	crabCounter = 0;
	bugCounter = 0;
	eggCounter = 0;

	wall1 = nullptr;
	wall2 = nullptr;
	wall3 = nullptr;
	spikes = nullptr;

	spring_cFrame = 0;
	spring_height = 64;
	spring_width = 64;
	spring_tFrame = 2;


	// loading world objecy texture
	wall1_tex.loadFromFile("Data/brick1.png");
	wall2_tex.loadFromFile("Data/brick2.png");
	wall3_tex.loadFromFile("Data/brick3.png");
	spike_tex.loadFromFile("Data/Spike.png");
	crystal_tex.loadFromFile("Data/crystal.png");
	spring_tex.loadFromFile("Data/spring_sprite.png");

	//springs.

	// collectibles textures
	ringAddress = "Data/ring.png";
	lifeAddress = "Data/health_sprite.png";
	powerAddress = "Data/extraLife.png";
	batBrainAddress = "Data/batBrain.png";


	rngMus.openFromFile("Data/ringCollect.wav");
	rngMus.setVolume(40);


	// the level background textures
	bg_tex = new Texture[4];
	bg_tex[0].loadFromFile("Data/level1_bg.png");
	bg_tex[1].loadFromFile("Data/level2_bg.png");
	bg_tex[2].loadFromFile("Data/level3_bg.png");
	bg_tex[3].loadFromFile("Data/levelB_bg.png");

	bg_sprite = new Sprite[4];
	bg_sprite[0].setTexture(bg_tex[0]);
	bg_sprite[1].setTexture(bg_tex[1]);
	bg_sprite[2].setTexture(bg_tex[2]);
	bg_sprite[3].setTexture(bg_tex[3]);

	for (int i = 0; i < 4; i++) {
		bg_sprite[i].setScale(1.2, 1);
	}
	
	/*lvl1 = new Music;
	lvl1->openFromFile("Data/labrynth.ogg");

	lvl2 = new Music;
	lvl2->openFromFile("Data/labrynth.ogg");

	lvl3 = new Music;
	lvl3->openFromFile("Data/labrynth.ogg");

	lvl4 = new Music;
	lvl4->openFromFile("Data/bossLevel.ogg");


	lvl1->setVolume(30);
	lvl2->setVolume(30);
	lvl3->setVolume(30);
	lvl4->setVolume(30);

	lvl1->setLoop(true);
	lvl2->setLoop(true);
	lvl3->setLoop(true);
	lvl4->setLoop(true);*/

}

// destructoe
levels::~levels()
{

	// deleteing all the positions
	delete[]eggPositions_x;
	delete[]eggPositions_y;

	delete[]beePositions_x;
	delete[]beePositions_y;

	delete[]bugPositions_x;
	delete[]bugPositions_y;

	delete[]brainPositions_x;
	delete[]brainPositions_y;

	delete[]crabPositions_x;
	delete[]crabPositions_y;


	delete[] bg_tex;
	delete[] bg_sprite;

	// deleting all the allets and the collectibles adn enemies
	for (int i = 0; i < height; i++) {
		delete[]lvl[i];
	}
	delete[]lvl;

	for (int i = 0; i < Total_rings; i++) {
		delete rng[i];
	}
	delete[]rng;

	for (int i = 0; i < Total_lives; i++) {
		delete life[i];
	}
	delete[]life;

	for (int i = 0; i < Total_powers; i++) {
		delete powers[i];
	}
	delete[]powers;

	for (int i = 0; i < Total_brain; i++) {
		delete brain[i];
	}
	delete[]brain;
	//delete[]brainPositions;

	for (int i = 0; i < Total_bee; i++) {
		delete bee[i];
	}
	delete[]bee;
	//delete[]beePositions;


	for (int i = 0; i < Total_bugs; i++) {
		delete bug[i];
	}
	delete[]bug;
	//delete[]bugPositions;


	for (int i = 0; i < Total_crabs; i++) {
		delete crab[i];
	}
	delete[]crab;
	//delete[]crabPositions;

	for (int i = 0; i < Total_eggStingers; i++) {
		delete egg[i];
	}
	delete[]egg;
	//delete[]eggPositions;


	//Deleting all the sprits
	delete wall1;
	delete wall2;
	delete wall3;
	delete spikes;
	delete crystals;
	delete springs;

}

void levels::builLevel()
{
	ifstream myfile;
	myfile.open(address);

	if (!myfile.is_open())
		cout << " Address file :  Error opening the file" << endl;

	string line;
	//std::string ringAddress = "Data/ring.png";

	int ringCount = 0;
	int lifeCount = 0;
	int powerCount = 0;

	int brainCounter = 0;
	int beeCount = 0;
	int bugCount = 0;
	int crabCount = 0;
	int eggCount = 0;

	for (int i = 0; i < height; i++) {
		getline(myfile, line);

		for (int j = 0; j < width; j++) {
			lvl[i][j] = line[j];
			Vector2f temp((float)j * cell_Size, (float)i * cell_Size);

			float temp_x = (float)j * cell_Size;
			float temp_y = (float)i * cell_Size;


			// first of all getting the position where something appeeard
			// then finding out waht actually appeared and then making it 
			// then positioning it, and also storing its position 
			// then in the display funcition displaying it with the offset


			if (lvl[i][j] == 'r' && ringCount < Total_rings) {


				//ring[count++].setAttributes(ringAddress, temp.x, temp.y);
				rng[ringCount] = new rings;
				rng[ringCount++]->setAttributes(ringAddress, temp_x, temp_y);

				ringCounter++;

			}


			if (lvl[i][j] == 'l' && lifeCount < Total_lives) {
				life[lifeCount] = new extra_life;
				life[lifeCount++]->setAttributes(lifeAddress, temp_x, temp_y);
				lifeCounter++;
			}

			if (lvl[i][j] == 'p' && powerCount < Total_powers) {
				powers[powerCount] = new power_ups;
				powers[powerCount++]->setAttributes(powerAddress, temp_x, temp_y);
				powerCounter++;
			}

			// Collectibles and enemies

			if (lvl[i][j] == 'e' && brainCounter < Total_brain) {
				brain[brainCounter] = new Bat_Brain;
				//temp.y -= 200.f;
				brain[brainCounter]->setAttributes(temp_x,temp_y);
				//brainPositions[brainCounter] = temp;

				brainPositions_x[brainCounter] = temp_x;
				brainPositions_y[brainCounter++] = temp_y;
				BrainCounter++;
			}

			if (lvl[i][j] == 'v' && beeCount < Total_bee) {
				bee[beeCount] = new Bee_bot;
				//temp.y -= 100.f;
				bee[beeCount]->setAttributes(temp_x, temp_y);
				//beePositions[beeCount++] = temp;
				beePositions_x[beeCount] = temp_x;
				beePositions_y[beeCount++] = temp_y;

				BeeCounter++;
			}

			if (lvl[i][j] == 'u' && bugCount < Total_bugs) {
				bug[bugCount] = new moto_bug;
				bug[bugCount]-> setAttributes(temp_x, temp_y);
				//bugPositions[bugCount++] = temp;

				bugPositions_x[bugCount] = temp_x;
				bugPositions_y[bugCount++] = temp_y;
				bugCounter++;
			}

			if (lvl[i][j] == 'c' && crabCount < Total_crabs) {
				crab[crabCount] = new crabMeat;
				crab[crabCount]->setAttributes(temp_x, temp_y);
				//crabPositions[crabCount++] = temp;

				crabPositions_x[crabCount] = temp_x;
				crabPositions_y[crabCount++] = temp_y;
				crabCounter++;
			}

			if (lvl[i][j] == 'g' && eggCount < Total_eggStingers) {
				egg[eggCount] = new eggStinger;
				egg[eggCount]->setAttributes(temp_x, temp_y);
				//eggPositions[eggCount++] = temp;

				eggPositions_x[eggCount] = temp_x;
				eggPositions_y[eggCount++] = temp_y;
				eggCounter++;
			}

		}
	}

	myfile.close();
}

// Displaying the levels
void levels::display_level(RenderWindow& window, float cameraOffset, Sprite& obj, int& levelIndex)
{

	// Setting the position of the player background
	bg_sprite[levelIndex].setPosition(0 - cameraOffset, 0);
	window.draw(bg_sprite[levelIndex]);

	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{
			if (lvl[i][j] == 'w')
			{
				wall1->setPosition(j * cell_Size - cameraOffset, i * cell_Size);
				window.draw(*wall1);
			}

			if (lvl[i][j] == 'q') {
				wall2->setPosition(j * cell_Size - cameraOffset, i * cell_Size);
				window.draw(*wall2);
			}

			if (lvl[i][j] == 'b') {
				wall3->setPosition(j * cell_Size - cameraOffset, i * cell_Size);
				window.draw(*wall3);
			}

			if (lvl[i][j] == 's') {
				spikes->setPosition(j * cell_Size - cameraOffset, i * cell_Size);
				window.draw(*spikes);
			}

			if (lvl[i][j] == 'x') {
				crystals->setPosition(j * cell_Size - cameraOffset, i * cell_Size);
				window.draw(*crystals);
			}

			if (lvl[i][j] == 'h') {
				springs->setPosition(j * cell_Size - cameraOffset, i * cell_Size);
				springAnimation();
				window.draw(*springs);
			}
		}
	}

	// Displaying the rings
	for (int i = 0; i < ringCounter; i++) {


		if (rng[i]->getPresentStatus()) {
			//Vector2f temp(rng[i]->getPosition().x - cameraOffset, rng[i]->getPosition().y);
			//rng[i]->setPosition(temp);
			rng[i]->CollectibleAnimation();
			rng[i]->render(window, cameraOffset);
		}
	}

	//Displaying the lives
	for (int i = 0; i < lifeCounter; i++) {
		if (life[i]->getPresentStatus()) {
			life[i]->CollectibleAnimation();
			life[i]->render(window, cameraOffset);
		}
	}

	//Displaying the powerups
	for (int i = 0; i < powerCounter; i++) {
		if (powers[i]->getPresentStatus()) {
			powers[i]->CollectibleAnimation();
			powers[i]->render(window, cameraOffset);
		}
	}

	//Displaying the enemies
	// BAT BRAINS
	for (int i = 0; i < BrainCounter; i++) {
		if (brain[i]->getStatus()) {

			// I am going to just set a threshold, if the player gets closer then the threshold the enemies will start to attack him

			if (ob->getsprite().getPosition().x - brain[i]->getPosition().x < 500) {
				bool b = true;
				brain[i]->setActivation(b);
			}
			else {
				bool b = false;
				brain[i]->setActivation(b);
			}

			/*if(brain[i]->getActivation())
				brain[i]->movements(obj);*/

			brain[i]->movements(obj, lvl);
		

			brain[i]->enemyAnimations();
			brain[i]->render(window, cameraOffset);
		}
	}

	// BEE BOTS
	for (int i = 0; i < BeeCounter; i++) {
		if (bee[i]->getStatus()) {
			bee[i]->shoot(window, cameraOffset);
			//// Checking projectiles colliison with the player
			//bool dummy = bee[i]->projectileCollision(*ob, cameraOffset);

			//// Checking projectiles collision with the world
			//bee[i]->projectileCollision_world(lvl, height, width);

			//// Checking the bees collision iwht the worlds
			//bee[i]->bee_collision(lvl);

			//// Movements and animations
			
			// it will only start moving when the player reaches a certain length into the level

			/*if (ob->getsprite().getPosition().x - bee[i]->getPosition().x < 700) {
				bool b = true;
				bee[i]->setActivation(b);
			}
			else {
				bool b = false;
				bee[i]->setActivation(b);
			}
			*/
			//if(bee[i]->getActivation())
				bee[i]->movements(obj);

			bee[i]->enemyAnimations();
			bee[i]->render(window, cameraOffset);
		}
	}


	// Moto bugs
	for (int i = 0; i < bugCounter; i++) {
		if (bug[i]->getStatus()) {

			if (ob->getsprite().getPosition().x > bug[i]->getPosition().x) {
				/*if (ob->getsprite().getPosition().x - bug[i]->getPosition().x < 1000) {
					bug[i]->movement(*ob);
				}*/
				bug[i]->movement(*ob, lvl);
			}
			else {
				if (bug[i]->getPosition().x - ob->getsprite().getPosition().x < 1000) {
					bug[i]->movement(*ob, lvl);
				}
			}

			bug[i]->enemyAnimations();
			bug[i]->render(window, cameraOffset);

		}
	}


	// Crab meats
	for (int i = 0; i < crabCounter; i++) {
		if (crab[i]->getStatus()) {

			if (ob->getsprite().getPosition().x > crab[i]->getPosition().x) {
				if (ob->getsprite().getPosition().x - crab[i]->getPosition().x < 1000) {
					crab[i]->movement(lvl);
				}
			}
			else {
				if (crab[i]->getPosition().x - ob->getsprite().getPosition().x < 1000) {
					crab[i]->movement(lvl);
				}
			}

			crab[i]->enemyAnimations();
			crab[i]->render(window, cameraOffset);

		}
	}


	// Displaying the egg stingers
	for (int i = 0; i < eggCounter; i++) {
		if (egg[i]->getStatus()) {

			egg[i]->movement(obj, lvl);
			egg[i]->enemyAnimations();
			egg[i]->render(window, cameraOffset);
			egg[i]->renderProjectile(window, cameraOffset);
		}
	}
}

void levels::setPlayer(Player* o)
{
	ob = o;
}

char** levels::getLevel()
{
	return lvl;
}

void levels::reset()
{
	bool b = true;

	/*for (int i = 0; i < ringCounter; i++) {
		rng[i]->setStatus(b);
	}

	for (int i = 0; i < lifeCounter; i++) {
		life[i]->setStatus(b);
	}

	for (int i = 0; i < powerCounter; i++) {
		powers[i]->setStatus(b);
	}*/


	for (int i = 0; i < Total_rings; i++) {
		delete rng[i];
	}
	delete[]rng;


	for (int i = 0; i < Total_lives; i++) {
		delete life[i];
	}
	delete[]life;

	for (int i = 0; i < Total_powers; i++) {
		delete powers[i];
	}
	delete[]powers;

	rng = new rings * [Total_rings];
	life = new extra_life * [Total_lives];
	powers = new power_ups * [Total_powers];

	for (int i = 0; i < Total_rings; i++) rng[i] = nullptr;
	for (int i = 0; i < Total_lives; i++) life[i] = nullptr;
	for (int i = 0; i < Total_powers; i++) powers[i] = nullptr;

	// BAT BRAINS
	for (int i = 0; i < BrainCounter; i++) {
		brain[i]->setStatus(b);
		brain[i]->setPosition(brainPositions_x[i], brainPositions_y[i]);
		brain[i]->setHp(brain[i]->getHealth());
	}

	// BEE BOTS
	for (int i = 0; i < BeeCounter; i++) {
		bee[i]->setStatus(b);
		bee[i]->setPosition(beePositions_x[i], beePositions_y[i]);
		bee[i]->setHp(bee[i]->getHealth());
	}

	// Moto bug
	for (int i = 0; i < bugCounter; i++) {
		bug[i]->setStatus(b);
		bug[i]->setPosition(bugPositions_x[i], bugPositions_y[i]);
		bug[i]->setHp(bug[i]->getHealth());
	}


	// Crab Meat
	for (int i = 0; i < crabCounter; i++) {
		crab[i]->setStatus(b);
		crab[i]->setPosition(crabPositions_x[i], crabPositions_y[i]);
		crab[i]->setHp(crab[i]->getHealth());
	}

	// Eggstinger
	for (int i = 0; i < eggCounter; i++) {
		egg[i]->setStatus(b);
		egg[i]->setPosition(eggPositions_x[i], eggPositions_y[i]);    ///         Problem here
		egg[i]->setHp(egg[i]->getHealth());
	}

	ringCounter = 0;
	lifeCounter = 0;
	powerCounter = 0;
	BrainCounter = 0;
	BeeCounter = 0;
	bugCounter = 0;
	crabCounter = 0;
	eggCounter = 0;
	ringCollectedCount = 0;


	builLevel();

}

void levels::checkCollision(Sprite& obj, Player& obj2, int& specialAbilityCounter, float cameraOffset, bool& bottomCollision, bool& jumping, bool& onground)
{

	/*Vector2f playerSize(
		obj.getTextureRect().width *
		obj.getScale().x,
		obj.getTextureRect().height *
		obj.getScale().y
	);*/


	//Checking collisions with the rings
	for (int i = 0; i < ringCounter; i++) {

		if (rng[i]->getPresentStatus()) {
			bool dummy = rng[i]->collision(obj, cameraOffset);
			if (dummy) {
				rngMus.play();
				ringCollectedCount++;
				*score += 10;
			}
		}
	}

	//Checking collisiosn with the lifes
	for (int i = 0; i < lifeCounter; i++) {

		if (life[i]->getPresentStatus()) {
			if (life[i]->collision(obj, cameraOffset))
				obj2.increaseHealth();
		}
	}

	//Checking collision with the powers
	for (int i = 0; i < powerCounter; i++) {

		if (powers[i]->getPresentStatus()) {
			bool powerCollision = powers[i]->collision(obj, cameraOffset);
			if (powerCollision)
				specialAbilityCounter += 2;
		}
	}

	// Checking collison with the brain bot
	for (int i = 0; i < BrainCounter; i++) {
		if (brain[i]->getStatus()) {
			//bool collision = brain[i]->collision(obj, bottomCollision);

			//bool collision = brain[i]->collision(obj2.getPosition(), playerSize, obj2.getVelocity().y, bottomCollision);

			//brain[i]->playerCollision(*ob);

			//if (!collision) {
			//	if (brain[i]->playerCollision(obj)) {
			//		obj2.reduceHealth();
			//		//std::cout << "Collision detected:" << std::endl;
			//	}
			//}

			brain[i]->handlePlayerCollision(ob, jumping, onground, score, "E");

			
		}
	}

	//Checking collision with the bee bot
	for (int i = 0; i < BeeCounter; i++) {
		if (bee[i]->getStatus()) {
			//bool collision = bee[i]->collision(obj, bottomCollision);

			//bool collision = bee[i]->collision(obj2.getPosition(), playerSize, obj2.getVelocity().y, bottomCollision);


			// Checking projectiles colliison with the player
			if (bee[i]->projectileCollision(*ob, cameraOffset))
			{
				if(obj2.getDamageStatus())
					obj2.reduceHealth();

			}


			// Checking projectiles collision with the world
			bee[i]->projectileCollision_world(lvl, height, width);

			// Checking the bees collision iwht the worlds
			//bee[i]->bee_collision(lvl);


			bee[i]->handlePlayerCollision(ob, jumping, onground, score, "E");
			// Checking the bees collision with the player to reduce health of the player
			//bee[i]->playerCollision(*ob);


			//if (!collision) {

			//	if (bee[i]->playerCollision(obj)) {
			//		obj2.reduceHealth();
			//		//std::cout << "Collision detected:" << std::endl;
			//	}

			//}
			
		}
	}

	// Checking collision with the moto bug
	for (int i = 0; i < bugCounter; i++) {
		if (bug[i]->getStatus()) {

			//bool collision = bug[i]->collision(obj, bottomCollision);
			
			//bool collision = bug[i]->collision(obj2.getPosition(), playerSize, obj2.getVelocity().y, bottomCollision);


			//if (!collision) {
			//	if (bug[i]->playerCollision(obj)) {
			//		obj2.reduceHealth();
			//		//std::cout << "Collision detected:" << std::endl;
			//	}

			//}
			
			//bug[i]->playerCollision(*ob);
			bug[i]->handlePlayerCollision(ob, jumping, onground, score, "E");
		}
	}

	// Checking collisions for moto bug
	for (int i = 0; i < crabCounter; i++) {
		if (crab[i]->getStatus()) {

			//bool collision = crab[i]->collision(obj, bottomCollision);
			//crab[i]->playerCollision(*ob);
			//bool collision = bug[i]->collision(obj2.getPosition(), playerSize, obj2.getVelocity().y, bottomCollision);


			//if (!collision) {

			//	if (crab[i]->playerCollision(obj)) {
			//		crab[i]->setMotion();
			//		obj2.reduceHealth();
			//		//std::cout << "Collision detected:" << std::endl;
			//	}

			//}

			if (crab[i]->handlePlayerCollision(ob, jumping, onground, score, "E")) {
				//obj2.reduceHealth();
			}
		}
	}

	for (int i = 0; i < eggCounter; i++) {
		if (egg[i]->getStatus()) {
			bool dummy = egg[i]->projectileMovement(lvl, ob);
			dummy = egg[i]->handlePlayerCollision(ob, jumping, onground, score, "B");

			cout << "Egg Stinger's health : " << egg[i]->getHp() << endl;
		}
	}
}

float& levels::getElapsedTime()
{
	elapsedTime = maxTime - timeClock.getElapsedTime().asSeconds();
	return elapsedTime;
}

void levels::setClock()
{
	timeClock.restart();
}

int& levels::ringCollectCount()
{
	// TODO: insert return statement here
	return ringCollectedCount;
}

void levels::setScore(int* a)
{
	score = a;
}

void levels::removeWall()
{
	bool found = false;
	for (int i = 0; i < eggCounter; i++) {
		if (egg[i]->getStatus()) {
			found = true;
		}
	}

	if (!found) {
		ringCollectedCount = ringCounter;

	}
}

void levels::playMusic(int& levelIndex)
{
	std::cout << "Playing the music" << endl;


	switch (levelIndex)
	{
	case 0: lvl1->play();
		lvl2->stop();
		lvl3->stop();
		lvl4->stop();
		break;

	case 1: lvl2->play();
		lvl1->stop();
		lvl3->stop();
		lvl4->stop();
		break;
		
	case 2: lvl3->play();
		lvl1->stop();
		lvl2->stop();
		lvl4->stop();
		break;

	case 3: lvl4->play();
		lvl1->stop();
		lvl2->stop();
		lvl3->stop();
		break;

	default:
		break;
	}
}

void levels::stopMusic(int& levelIndex)
{
	cout << "Stopping the music" << endl;
	switch (levelIndex)
	{
	case 0: lvl1->pause();
		
		/*lvl2->play();
		lvl3->play();
		lvl4->play();*/
		break;

	case 1: lvl2->pause();
		/*lvl1->play();
		lvl3->play();
		lvl4->play();*/
		break;

	case 2: lvl3->pause();
		/*lvl1->play();
		lvl2->play();
		lvl4->play();*/
		break;

	case 3: lvl4->pause();
		/*lvl1->play();
		lvl2->play();
		lvl3->play();*/
		break;

	default:
		break;
	}
}


//int& levels::getHeight()
//{
//	return height;
//	// TODO: insert return statement here
//}
//
//int& levels::getWidth()
//{
//	return width;
//	// TODO: insert return statement here
//}
