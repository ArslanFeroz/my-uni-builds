#include "Player.h"
#include <iostream>

void Player::setIndexes(int x, int y)
{
	index1 = x;
	index2 = y;
}

void Player::updateFlight(bool& onGround, char** lvl)
{
	
	if (onGround && !Keyboard::isKeyPressed(Keyboard::Z)) {
		flyClock.restart();
		isFlying = false;
	}

	// 2) If Z is down *and* we still have time left, ascend.
	if (Keyboard::isKeyPressed(Keyboard::Z)
		&& flyClock.getElapsedTime().asSeconds() < maxFlyTime)
	{
		//Vector2f p = getPosition();
		float p_x = getPosition_x();
		float p_y = getPosition_y();

		if (!CollisionWithGround(lvl)) {
			p_y -= 50 * 0.5;
			setPosition(p_x, p_y);
		}
		

		isFlying = true;       
		onGround = false;   
	}


}

void Player::saveGame(float& x, float& y, int health)
{

	std::fstream myfile;
	myfile.open("Data/data.txt", ios::app);
	while (myfile.is_open()) {

		myfile << x << ' ' << y << ' ' << health << '\n';

		myfile.close();
	}

}

void Player::truncateFile()
{
	fstream myfile;
	myfile.open("Data/data.txt", ios::out | ios::trunc);
	myfile.close();
	//return 0;
}

void Player::loadFromSave(float x, float y, int hp)
{
	position_x = x;
	position_y = y;

	setHealth(hp);

}

Player::Player():
  scale_x(2.5f)
, scale_y(2.5f)
, raw_img_x(24)
, raw_img_y(35)
, currentVelocity(0)
{
	scale_x = 2.5;
	scale_y = 2.5;

	velocity_x = 10;
	velocity_y = -20; // initial jump velocity;

	main = false;
	hp = 3;
	SpecialAbilityCounter = 20;
	noDamage = false;
	flyClock.restart();

	Pheight = raw_img_y * scale_y;
	Pwidth = raw_img_x * scale_x;
	hit_box_factor_x = int(8 * scale_x);
	hit_box_factor_y = int(5 * scale_y);

}

Player::Player(Vector2f& pos): currentVelocity(0)
{
	scale_x = 2.5;
	scale_y = 2.5;

	velocity_x = 10;
	velocity_y = -20; // initial jump velocity;


	position_x = pos.x;
	position_y = pos.y;
}

// Setting all the textures
void Player::setTexture(std::string& address, std::string& address2, std::string& address3, std::string& address4, std:: string& address5, std::string& address6)
{

	// Settign all the textures
	rightStill.loadFromFile(address);
	sprite.setTexture(rightStill);
	sprite.setScale(scale_x, scale_y);
	sprite.setPosition(position_x, position_y);

	// additonal texture
	leftStill.loadFromFile(address2);
	leftMotion.loadFromFile(address3);
	rightMotion.loadFromFile(address4);

	leftJump.loadFromFile(address5);
	rightJump.loadFromFile(address6);
}

// Jump mechanism for the palyers
void Player::jump(bool& jumping, bool& onground, float gravity, char** lvl, int Pwidth, int hit_box_factor_x, int hit_box_factor_y, int cell_size, bool onSpring)
{
	// If the player is no ground the velocity is different if it is on the spring it is different
	if (onground) {

		if (onSpring) {

			velocity_y = -30;
			onSpring = false;
		}
		else
			velocity_y = -20;
		onground = false;
		jumping = true;
	}

	

	if (jumping) {

		bool upperColliison = false;

		int offset_y = position_y + velocity_y;
		int player_x = position_x;

		
		int rowAbove = int((offset_y - hit_box_factor_y) / cell_size);

		
		int colLeft = int((player_x + hit_box_factor_x) / cell_size);
		int colRight = int((player_x + hit_box_factor_x + Pwidth) / cell_size);
		int colMid = int((player_x + hit_box_factor_x + Pwidth / 2) / cell_size);

		
		char top_left = lvl[rowAbove][colLeft];
		char top_right = lvl[rowAbove][colRight];
		char top_mid = lvl[rowAbove][colMid];

		/*int height = lv.getHeight();
		int width = lv.getWidth();*/

		if (rowAbove < 0 || rowAbove >= 14 ||
			colLeft < 0 || colLeft >= 300 ||     // willl change this part after
			colMid < 0 || colMid >= 300 ||
			colRight < 0 || colRight >= 300)
		{
			// just do the normal jump step:
			position_y += velocity_y;
			velocity_y += gravity;
			sprite.setPosition(position_x, position_y);
			if (velocity_y >= 0) jumping = false;
			return;
		}

		// If it hits thing like platforms and breakable wall from below collison should follow
		if (top_left == 'q' || top_right == 'q' || top_mid == 'q'  || top_left == 'b' || top_right == 'b' || top_mid == 'b') {
			upperColliison = true;
			velocity_y = 0;
		}


		if (!upperColliison) {

			position_y += velocity_y;     //move up
			velocity_y += gravity;        //gravity is applying
			sprite.setPosition(position_x, position_y);

		}

		

		// If the top of the fligt is reached then the jumpign has ender
		if (velocity_y >= 0) {        
			jumping = false;
		}

	}
}




// Movement mechanicsm of players
void Player::movement(Event& ev, float& player_x, bool& leftMovement, float& dt)
{
	// Formulating the velocity of horizontal motion in runtime, it depends from player to player
	currentVelocity += acceleration * dt;

	//cout << currentVelocity << endl;


	if (leftMovement) {

		//player_x -= velocity.x;
		player_x -= currentVelocity;
	}
	else {
		//player_x += velocity.x;
		player_x += currentVelocity;

	}

	// If it reaches max velocity then clamping it
	if (currentVelocity > velocity_x)
		currentVelocity = velocity_x;
}

// Checking collision iwht the world objects
bool Player::noCollision(char** lvl, float player_x, float player_y, int Pwidth, int Pheight, int hit_box_factor_x, int hit_box_factor_y, const int cell_size)
{

	// used the same method of collision used in gravity as provided in the skeliton code

	char left_mid = lvl[
		(int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size
	][
		(int)(player_x + hit_box_factor_x) / cell_size
	];

	char right_mid = lvl[
		(int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size
	][
		(int)(player_x + hit_box_factor_x + Pwidth) / cell_size
	];

	// If fall on spike then reducing health
	if (left_mid == 's' || right_mid == 's') {
		reduceHealth();
	}

	if ((left_mid == 'w' || right_mid == 'w') || (left_mid == 'q' || right_mid == 'q') || (left_mid == 'b' || right_mid == 'b')
		) {

		// If it strikes with the spikes then it will take damage
	
		
		return false;
	}


	return true;
}

// still state of the players (base on their previous direction of motions)
void Player::Still_State(Event& ev)
{
	if (ev.key.code == Keyboard::Right) {
		sprite.setTexture(rightStill);
		sprite.setTextureRect(IntRect(0, 0, 40, 40));

		
	}


	if (ev.key.code == Keyboard::Left) {
		sprite.setTexture(leftStill);
		sprite.setTextureRect(IntRect(0, 0, 40, 40));

	}
}

// Jog state of teh players
void Player::jogState(std::string& state, Clock& clock)
{
	// Computing on runtime for accuracy, (was having issue when kept them as data members)
	static int currentFrame = 0;
	const float switchTime = 0.1f;
	const int width = 40;
	const int height = 40;
	const int frameCount = 10;

	// animating it
	if (clock.getElapsedTime().asSeconds() > switchTime) {
		currentFrame++;
		if (currentFrame >= frameCount)
			currentFrame = 0;
		clock.restart();
	}

	// Choosing the sprite base of directions
	if (state == "R") {


		sprite.setTexture(rightMotion);
		sprite.setTextureRect(IntRect(currentFrame * width, 0, width, height));
	}
	else if (state == "L") {
		sprite.setTexture(leftMotion);
		sprite.setTextureRect(IntRect(currentFrame * width, 0, width, height));
	}
}


// Jump animation of the players ( the ball state )
void Player::jumpState(std::string& state, Clock& clock)
{
	static int currentFrame = 0;
	const float switchTime = 0.1f;
	const int width = 40;
	const int height = 40;
	const int frameCount = 8;

	if (clock.getElapsedTime().asSeconds() > switchTime) {
		currentFrame++;
		if (currentFrame >= frameCount)
			currentFrame = 0;
		clock.restart();
	}

	if (state == "R") {
		sprite.setTexture(rightJump);
		sprite.setTextureRect(IntRect(currentFrame * width, 0, width, height));
	}
	else if (state == "L") {
		sprite.setTexture(leftJump);
		sprite.setTextureRect(IntRect(currentFrame * width, 0, width, height));
	}
}

// Player gravity ( same code as the one provide in skeliton )
void Player::player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth, bool& onSpring)
{

	 // computign  the offsets of the players
	offset_y = player_y;

	offset_y += velocityY;


	// finding the next tile coordinates
	char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x) / cell_size];
	char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth) / cell_size];
	char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size];


	//Special case for spring
	if (bottom_left_down == 'h' || bottom_mid_down == 'h' || bottom_right_down == 'h') {
		onGround = true;
		onSpring = true;
	}


	// Chcking collision
	if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w')
		|| (bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q')
		|| (bottom_left_down == 'b' || bottom_mid_down == 'b' || bottom_right_down == 'b'))
	{
		onGround = true;
	}
	else
	{
		player_y = offset_y;
		onGround = false;
	}

	if (!onGround)
	{
		velocityY += gravity;
		if (velocityY >= terminal_Velocity) velocityY = terminal_Velocity;
	}

	else
	{
		velocityY = 0;
	}

	position_y = player_y;                
	sprite.setPosition(position_x, position_y);
}

void Player::draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y, float cameraOffset, bool on)
{
	if (on) {
		
		// If the player is the main character then clamping it to the centre of the screen and displaying other objects based on its offset
		float screenCenterX = window.getSize().x / 2.f;
		LstillSprite.setPosition(screenCenterX, player_y);
	}
	else {
		

		LstillSprite.setPosition(player_x - cameraOffset, player_y);
	}

	window.draw(LstillSprite);
}

Sprite& Player::getsprite()
{
	// TODO: insert return statement here
	return sprite;
}

//Vector2f& Player::getPosition()
//{
//	// TODO: insert return statement here
//	return position;
//}
//
//Vector2f Player::getVelocity()
//{
//	return velocity;
//}

bool& Player::getFlightStatus()
{
	return isFlying;
	// TODO: insert return statement here
}

float& Player::getPosition_x()
{
	return position_x;
	// TODO: insert return statement here
}

float& Player::getPosition_y()
{
	return position_y;
	// TODO: insert return statement here
}

float& Player::getVelocity_x()
{
	// TODO: insert return statement here
	return velocity_x;

}

float& Player::getVelocity_y()
{
	// TODO: insert return statement here
	return velocity_y;
}

//void Player::setPosition(float& x, float& y)
//{
//	position_x = x;
//	position_y = y;
//}


bool Player::getStatus()
{
	return main;
}

void Player::setSpeed(float& x, float& y)
{
	velocity_x = x;
	velocity_y = y;
}

void Player::setPosition(float& x, float & y)
{
	position_x = x;
	position_y = y;
}

void Player::increaseHealth()
{
	hp++;
}

void Player::deaccelaration(float& dt, float friction, bool& leftMovement, float& player_x)
{

	// applying the friction  ( through de accelaration )

	currentVelocity -= friction * dt;
	if (currentVelocity < 0)
		currentVelocity = 0;

	if (leftMovement) {
		player_x -= currentVelocity;
	}
	else
		player_x += currentVelocity;

	
}

float  Player::getCurrent_x()
{
	return currentVelocity;
}

void Player::setCurrentVelocity()
{
	currentVelocity = 0;
}

void Player::setDamageStatus()
{

	if (noDamage) {
		sprite.setColor(Color(255, 255, 255, 128));

		if (healthClock.getElapsedTime().asSeconds() > 3) {

			noDamage = !noDamage;
			sprite.setColor(Color(255, 255, 255, 255));

			//healthClock.restart();
		}

	}
	return;

}

void Player::setHealthClock()
{
	healthClock.restart();
}

void Player::setStatus(bool& s)
{
	main = s;
}

int& Player::getAbilityCounter()
{
	return SpecialAbilityCounter;
}

void Player::setNoDamage()
{
	noDamage = !noDamage;
}

bool Player::getDamageStatus()
{
	return noDamage;
}

// It is used to check the other characters a too far away from the main character
bool Player::PositionCheck(float& mainPosition_x, float& mainPosition_y)
{

	//Vector2f currentPosition = this->getPosition();
	float currentPosition_x = position_x;
	float currentPosition_y = position_y;

	if (mainPosition_x >= currentPosition_x + 10 * 64 || mainPosition_x <= currentPosition_x - 10 * 64)
		return true;

	// if they fall through the pit then respawning them
	else if (currentPosition_y >= 750)
		return true;


	return false;
}

// Function to move the player towards the main player
bool Player::moveTowardMain(float& mainPosition_x, float& mainPosition_y, bool& rightMotion)
{
	//Current object position
	//Vector2f currentPositon = this->getPosition();
	float currentPosition_x = position_x;
	float currentPosition_y = position_y;

	if (mainPosition_x > currentPosition_x + 2*this->getsprite().getTextureRect().width) {
		rightMotion = false;
		return true;
	}

	else if (mainPosition_x < currentPosition_x - 2 * this->getsprite().getTextureRect().width) {
		rightMotion = true;
		return true;
	}

	/*else if (mainPosition.x < currentPositon.x - 10) {
		leftMotion = true;
		return true;
	}*/



	return false;
}



//void Player::follow(const Vector2f& targetPos, float speed, float dt)
//{
//
//	Vector2f dir = targetPos - position;
//	float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//	if (len > 0.f) {
//		dir /= len;
//		position += dir * speed * dt;
//		sprite.setPosition(position);
//	}
//}

void Player::shiftCharacter(Event& ev, int& main_character_index, int& other1, int& other2)
{

	// If the q key is pressed then switching the character
	if (ev.key.code == Keyboard::Q) {

		if (main_character_index <= 1) {
			main_character_index++;
		}
		else {
			main_character_index = 0;
		}


		// Other positions
		other1 = (main_character_index + 1) % 3;
		other2 = (main_character_index + 2) % 3;
	}

}

bool Player::CollisionWithGround(char** lvl)
{

	int offset_y = position_y + velocity_y;
	int player_x = position_x;


	int rowAbove = int((offset_y - hit_box_factor_y) / cell_size);


	int colLeft = int((player_x + hit_box_factor_x) / cell_size);
	int colRight = int((player_x + hit_box_factor_x + Pwidth) / cell_size);
	int colMid = int((player_x + hit_box_factor_x + Pwidth / 2) / cell_size);


	char top_left = lvl[rowAbove][colLeft];
	char top_right = lvl[rowAbove][colRight];
	char top_mid = lvl[rowAbove][colMid];

	if (top_left == 'q' || top_right == 'q' || top_mid == 'q' || top_left == 'b' || top_right == 'b' || top_mid == 'b') {
		/*upperColliison = true;
		velocity.y = 0;*/

		return true;
	}
	else
		return false;



}



bool Player::breakAblewall(char** lvl, float player_x, float player_y, int Pwidth, int Pheight, int hit_box_factor_x, int hit_box_factor_y, const int cell_size, int& index1, int& index2, bool rightMOtion)
{
	// Using the same logic of hitboxes and offsets to get the next tile If it si breakable then breaking it with the knuckles

	char left_mid = lvl[
		(int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size
	][
		(int)(player_x + hit_box_factor_x) / cell_size
	];

	char right_mid = lvl[
		(int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size
	][
		(int)(player_x + hit_box_factor_x + Pwidth) / cell_size
	];

	if (left_mid == 'b' || right_mid == 'b') {

		if (rightMOtion) {
			index1 = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
			index2 = (int)(player_x + hit_box_factor_x + Pwidth) / cell_size;

		}
		else {

			index1 = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
			index2 = (int)(player_x + hit_box_factor_x) / cell_size;
		}


		//std::cout << "Breakable wall detected with indexes : " << index1 << " " << index2 << std::endl;

		return true;

	}


	return false;
}


void Player::reduceHealth()
{

	// If the player is invincible them not reducing its health
	if (noDamage) {
		return;
	}
	else {
		hp--;
		noDamage = true;
		healthClock.restart();
	}


}

int Player::gethealth()
{
	return hp;
}

void Player::setHealth(int x)
{
	hp = x;
}





