#pragma once

#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"

using namespace sf;

class collectibles
{

private:
	
	bool presentStatus;
	std::string address;
	const float scale_x = 2.5;
	const float scale_y = 2.5;

protected:
	Sprite *sprite;
	Texture *spriteSheet;
	int width;
	int height;
	Vector2f position;
	//Animation clock
	Clock clock;

	void setData(std::string& ad, int h, int w, float& x, float& y);


public:
	collectibles();
	//collectibles(const std::string& address, int h, int w);
	virtual void CollectibleAnimation() = 0;
	virtual ~collectibles();

	Vector2f getPosition();

	bool getPresentStatus();
	void setPosition(Vector2f& position);
	void setPosition(float& x, float& y);
	void setStatus(bool& b);



	bool collision(Sprite& obj, float cameraOffset);


	
	//rendering
	void render(RenderWindow& window, float cameraOffset);
};




