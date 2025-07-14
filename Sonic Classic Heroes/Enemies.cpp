#include "Enemies.h"
#include "iostream"

// This is the funciton useed by the derived classes to set the data of the main class, could also have used protected mmebrs but wanter
// to make it more secure 
// also it made debugging alot easier
void Enemies::setData(std::string& ad, int h, int w, float& x, float& y, int health, float scale_x = 1.8, float scale_y  = 1.8)
{

	address = ad;
	height = h;
	width = w;
	position.x = x;
	position.y = y;

	this->scale_x = scale_x;
	this->scale_y = scale_y;

	hp = health;

	sprite = new Sprite;
	spriteSheet = new Texture;
	spriteSheet->loadFromFile(ad);

	sprite->setTexture(*spriteSheet);
	sprite->setTextureRect(IntRect(0, 0, width, height));

    sprite->setScale(scale_x, scale_y);

	
}

Enemies::Enemies()
{
	presentStatus = true;
	sprite = nullptr;
	spriteSheet = nullptr;

}

Enemies::~Enemies()
{
	delete sprite;
	delete spriteSheet;
}

void Enemies::setStatus(bool& b)
{
	presentStatus = b;
}

void Enemies::setPosition(Vector2f& pos)
{
	position.x = pos.x;
	position.y = pos.y;
}

void Enemies::setPosition(float& x, float& y)
{
	position.x = x;
	position.y = y;
}

Vector2f Enemies::getPosition()
{
	return position;
}

bool Enemies::getStatus()
{
	return presentStatus;
}

void Enemies::setScale(float& x, float& y)
{
	scale_x = x;
	scale_y = y;
}




// returns true (and sets bottomCollision=true) only when the player lands on the top of the enemy
//bool Enemies::collision(Sprite& obj, bool& bottomCollision)
//{
//    if (!presentStatus)
//        return false;
//
//    // 1) Player AABB
//    float px = obj.getPosition().x;
//    float py = obj.getPosition().y;
//    float pw = float(obj.getTextureRect().width);
//    float ph = float(obj.getTextureRect().height);
//
//    // 2) Enemy AABB
//    float ex = position.x;
//    float ey = position.y;
//    float ew = width * sprite->getScale().x;
//    float eh = height * sprite->getScale().y;
//
//    // 3) Quick reject if no overlap
//    if (px + pw <= ex || px >= ex + ew ||
//        py + ph <= ey || py >= ey + eh)
//    {
//        return false;
//    }
//
//    // 4) Compute penetration on each side
//    float penLeft = (px + pw) - ex;      // how far player intrudes from left
//    float penRight = (ex + ew) - px;      // from right
//    float penDown = (py + ph) - ey;      // from above onto enemy top
//    float penUp = (ey + eh) - py;      // from below
//
//    // 5) pick the smaller on X and on Y manually
//    float penX = (penLeft < penRight ? penLeft : penRight);
//    float penY = (penDown < penUp ? penDown : penUp);
//
//    // 6) only treat as a "stomp" if vertical penetration is shallower
//    //    AND it came from above (penDown > 0)
//    if (penY < penX && penDown > 0.f)
//    {
//        bottomCollision = true;
//        if (--hp <= 0)
//            presentStatus = false;
//        return true;
//    }
//
//    // otherwise it was a side?hit or bottom?hit — ignore
//    return false;
//}

//bool Enemies::collision(const Vector2f& pwPos, const Vector2f& pwSize, float playerVelY, bool& bottomCollision)
//{
//    if (!presentStatus) return false;
//
//    // Enemy AABB in world space:
//    float ex = position.x;
//    float ey = position.y;
//    float ew = width * sprite->getScale().x;
//    float eh = height * sprite->getScale().y;
//
//    // Player AABB in world space:
//    float px = pwPos.x;
//    float py = pwPos.y;
//    float pw = pwSize.x;
//    float ph = pwSize.y;
//
//    // Quick reject:
//    if (px + pw <= ex || px >= ex + ew ||
//        py + ph <= ey || py >= ey + eh)
//    {
//        return false;
//    }
//
//    // Compute intersection rectangle:
//    float overlapX = std::min(px + pw, ex + ew) - std::max(px, ex);
//    float overlapY = std::min(py + ph, ey + eh) - std::max(py, ey);
//
//    // Only treat as a “stomp” if:
//    //   a) vertical penetration is smaller than horizontal,
//    //   b) player was falling (velY > 0).
//    if (overlapY < overlapX && playerVelY > 0.f)
//    {
//        bottomCollision = true;
//        if (--hp <= 0) presentStatus = false;
//        return true;
//    }
//
//    // otherwise it’s a side?hit or the player is jumping up through it…
//    return false;
//}
//
//// returns true if the player overlaps this enemy at all (side or bottom hit)
//bool Enemies::playerCollision(Sprite& ob)
//{
//    if (!presentStatus)
//        return false;
//
//    float px = ob.getPosition().x;
//    float py = ob.getPosition().y;
//    float pw = float(ob.getTextureRect().width);
//    float ph = float(ob.getTextureRect().height);
//
//    float ex = position.x;
//    float ey = position.y;
//    float ew = width * sprite->getScale().x;
//    float eh = height * sprite->getScale().y;
//
//    bool overlapX = (px + pw > ex) && (px < ex + ew);
//    bool overlapY = (py + ph > ey) && (py < ey + eh);
//
//    return (overlapX && overlapY);
//}
//
//
//




bool Enemies::handlePlayerCollision(Player* player, bool& jumping, bool& inFlight, int* score, const string str = "E")
{
    if (!presentStatus) return false;


    // Getting all player coordinates

	float player_x = player->getPosition_x();
	float player_y = player->getPosition_y();

	Sprite& play = player->getsprite();

    // Calculating the width of teh players
    float player_width = play.getTextureRect().width * play.getScale().x;
    float player_height = play.getTextureRect().height * play.getScale().y;


    // Getting all the coordinates of the enemies
    float enemy_x = this->position.x;
    float enemy_y = this->position.y;

    float enemy_width = this->width * sprite->getScale().x;
    float enemy_height = this->height * sprite->getScale().y;


	//cout << "Jump status " << jumping << endl;
    // Checking the collision
	// Adding tolerances to make the collision more better
	float tolerance = 0.f;
	if (str != "E")
		tolerance = -20.f;

    if (player_x + player_width > enemy_x - tolerance  
		&& player_x < enemy_x + enemy_width + tolerance  
		&& player_y + player_height - tolerance > enemy_y 
		&& player_y < enemy_y + enemy_height + tolerance) {

        // If it collided and player was in jump state like, in ball form then enemy takes the damage other wise the player takes the damage
        /*float penetration = (player_y + player_height) - enemy_y;
        const float tolerance = 5.0f;*/

		// If the plaeyr is inflight then the enemey takes damage
		if (inFlight) {


			//--hp;

			if (str == "E") {
				--hp;
			}
			else {
				if (jumping) {
					hp--;
					jumping = false;
				}

			}

			
            if (hp <= 0) {
				//std::cout << "Enemy is taking the damage" << std::endl;

                presentStatus = false;
				*score += 100;

			}
			else
				return true;

			
        }
		// Player takes the damage
        else {

            //std::cout << "Player is taking the damage" << std::endl;

			

			if (!player->getDamageStatus()) {
				player->reduceHealth();

				//player->setDamageStatus();

			}
        }

    }

	

    return true;



}

// Checing collison of the enemies with hte world objects
bool Enemies::noCollision(char** lvl, float player_x, float player_y)
{
	// Same logic of hitboxes 
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

	if ((left_mid == 'w' || right_mid == 'w') || (left_mid == 'q' || right_mid == 'q') || (left_mid == 'b' || right_mid == 'b')
		) {


		return false;
	}


	return true;

}

void Enemies::setHp(int h)
{
    hp = h;
}

int Enemies::getHp()
{
	return hp;
}

// rendering the enemies with respect to the offsets
void Enemies::render(RenderWindow& window, float offsetX)
{
	sprite->setPosition(position.x - offsetX, position.y);
	window.draw(*sprite);
}










//bool Enemies::collision(Sprite& obj, bool& bottomCollision)
//{
//
//    if (!presentStatus)
//        return false;
//
//    // 1) compute the player bounds
//    float px = obj.getPosition().x;
//    float py = obj.getPosition().y;
//    float pw = static_cast<float>(obj.getTextureRect().width);
//    float ph = static_cast<float>(obj.getTextureRect().height);
//
//   
//    float ex = position.x;
//    float ey = position.y;
//    float ew = width * sprite->getScale().x;
//    float eh = height * sprite->getScale().y;
//
//    bool overlapX = (px + pw > ex) && (px < ex + ew);
//    bool overlapY = (py + ph > ey) && (py < ey + eh);
//    if (!(overlapX && overlapY))
//        return false;
//
// 
//    float playerCenterY = py + ph * 0.5f;
//    float enemyCenterY = ey + eh * 0.5f;
//    if (playerCenterY < enemyCenterY) {
//       
//        bottomCollision = true;
//        std::cout << "Landed on top" << std::endl;
//
//        hp -= 1;
//        if (hp <= 0)
//            presentStatus = false;
//        return true;
//    }
//
//    // otherwise it was a side or bottom hit—ignore for "landing on top"
//    return false;
//}
//
//bool Enemies::playerCollision(Sprite& ob)
//{
//    if (presentStatus) {
//
//        
//
//        // computing the player bounds
//        float px = ob.getPosition().x;
//        float py = ob.getPosition().y;
//        float pw = static_cast<float>(ob.getTextureRect().width);
//        float ph = static_cast<float>(ob.getTextureRect().height);
//
//
//        float ex = position.x;
//        float ey = position.y;
//        float ew = width * sprite->getScale().x;
//        float eh = height * sprite->getScale().y;
//
//        bool overlapX = (px + pw > ex) && (px < ex + ew);
//
//        if (overlapX)
//            return true;
//        else
//            return false;
//        //if (overlapX) {
//        //    ob; // reducing the health point of the player by one
//        //}
//
//    }
//         
//
//   
//}

