#include "Player.h"
#include "Constants.h"

// Used new constructor syntax in .h

void Player::setCoord(Coord c)
{
	this->x = c.x;
	this->y = c.y;
}

Coord Player::getCoord()
{
	Coord c;
	c.x = this->x;
	c.y = this->y;
	return c;
}

char Player::getSprite()
{
	return this->sprite;
	return this->sprite;
}

void Player::addGravity() {
	vy += GRAVITY;
	if (y + vy > SCREEN_HEIGHT - 1) {
		y = SCREEN_HEIGHT - 1;
		vy = 0;
	}
}

void Player::jump() {
    if (this->onGround()) {
        vy += JUMP_VELOCITY;
    } 
}

bool Player::onGround() {
    return y == SCREEN_HEIGHT - 1;
}

void Player::updatePosition() {
    if (this->onGround() && vy > 0) {
        vy = 0;
    }
    else {
        vy += GRAVITY;
    }

    // Check boundaries for horizontal movement
    if ((vx < 0 && (x + vx) >= 0) || (vx > 0 && (x + vx) < SCREEN_WIDTH)) {
        x += vx;
    }

    // Check boundaries for vertical movement
    if ((vy < 0 && (y + vy) >= 0) || (vy > 0 && (y + vy) < SCREEN_HEIGHT)) {
        y += vy;
    }
}