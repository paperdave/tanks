#include "pch.h"
#include "Player.h"

Player::Player(sf::Vector2i position, int playerID) {
	hue = hue;

	controls = getPlayerControlsByID(playerID);
	dir = rand() % 360;
	x = 60 * (position.x) + 30;
	y = 60 * (position.y) + 30;
	bounds.width = 30;
	bounds.height = 30;
	id = playerID;
}

void Player::HandleKeypress(int code, bool state) {
	if (code == controls.up) {
		this->keyFoward = state;
	}
	else if (code == controls.down) {
		this->keyBackwards = state;
	}
	else if (code == controls.left) {
		this->keyLeft = state;
	}
	else if (code == controls.right) {
		this->keyRight = state;
	}
	else if (code == controls.action) {
		// one way
		if (state)
			this->keyAction = true;
		if (state == false) this->keyAction = false;
	}
}
