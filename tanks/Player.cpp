#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "Utility.h"
#include "Resources.h"

Player::Player(sf::Vector2i position, int playerID) {
	type = GameObjectType::Player;

	switch (playerID) {
	case 1: color = player1Color; break;
	case 2: color = player2Color; break;
	case 3: color = player3Color; break;
	case 4: color = player4Color; break;
	}

	controls = getPlayerControlsByID(playerID);
	dir = rand() % 360;
	x = 60 * (position.x) + 30;
	y = 60 * (position.y) + 30;
	bounds.width = 30;
	bounds.height = 30;
	id = playerID;
}

// Keybinds
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

void Player::update() {
	dir = fmod(dir, 360) + 360;
	if (keyLeft == true) {
		dir -= turnSpeed;
	}
	if (keyRight == true) {
		dir += turnSpeed;
	}
	double move_x = 0;
	double move_y = 0;
	if (keyFoward) {
		move_x += lengthdir_x(speed, dir);
		move_y += lengthdir_y(speed, dir);
	}
	if (keyBackwards) {
		move_x -= lengthdir_x(this->speed, this->dir);
		move_y -= lengthdir_y(this->speed, this->dir);
	}

	while (collisionAt(x + move_x, y)) {
		move_x -= sign(move_x) * 0.1;
	}
	while (collisionAt(x + move_x, y + move_y)) {
		move_y -= sign(move_y) * 0.1;
	}

	x += move_x;
	y += move_y;

	if (keyAction) {
		keyAction = false;
		gunOffset = 20;
		
		createObject(new Bullet(x + lengthdir_x(10, dir - 4), y + lengthdir_y(10, dir - 4), dir));
	}

	gunOffset *= 0.5;
}

void Player::render(sf::RenderTarget* g) {
	sf::Texture &texL0 = getTexture("tank0/layer0");
	sf::Texture &texL1 = getTexture("tank0/layer1");
	sf::Texture &texL2 = getTexture("tank0/layer2");
	sf::Texture &texL3 = getTexture("tank0/layer3");
	sf::Texture &texL4 = getTexture("tank0/layer4");
	sf::Texture &texL5 = getTexture("tank0/layer5");
	sf::Texture &texL6 = getTexture("tank0/layer6");
	sf::Sprite sTop;

	int sat = wave(255, 0, 0.8, 0);

	sTop.setTexture(texL0);
	sTop.setScale(0.7, 0.7);
	sTop.setOrigin(sTop.getLocalBounds().width / 2 * 0.8, sTop.getLocalBounds().height / 2);

	sTop.setRotation(dir);
	sTop.setColor(color);

	sTop.setPosition(x, y);

	sf::Sprite sBot;

	sBot.setTexture(texL4);
	sBot.setScale(0.7, 0.7);
	sBot.setOrigin(sTop.getOrigin());

	sBot.setRotation(dir);
	sBot.setColor(color);

	sBot.setPosition(x + lengthdir_x(-gunOffset, (double)dir), y + lengthdir_y(-gunOffset, dir) - 4);

	g->draw(sTop);
	
	sTop.move(0, -1);
	g->draw(sTop);
	
	sTop.setTexture(texL1);
	sTop.move(0, -1);
	g->draw(sTop);

	sTop.setTexture(texL2);
	sTop.move(0, -1);
	g->draw(sTop);
	
	sTop.setTexture(texL3);
	sTop.move(0, -1);
	g->draw(sTop);

	g->draw(sBot);
	
	sBot.setTexture(texL5);
	sBot.move(0, -1);
	g->draw(sBot);

	sBot.setTexture(texL6);
	sBot.move(0, -1);
	g->draw(sBot);

}

// Collision
bool Player::collisionSquare(int squareX, int squareY) {
	Maze maze = getMaze();
	if (maze.wallDown(squareX, squareY, false)) {
		int rectLeft = squareX * 60;
		int rectTop = squareY * 60 + 60 - 2;
		if (this->bounds.intersects(sf::FloatRect(rectLeft, rectTop, 60, 4))) {
			return true;
		}
	}
	if (maze.wallUp(squareX, squareY, false)) {
		int rectLeft = squareX * 60;
		int rectTop = squareY * 60 - 2;
		if (this->bounds.intersects(sf::FloatRect(rectLeft, rectTop, 60, 4))) {
			return true;
		}
	}
	if (maze.wallLeft(squareX, squareY, false)) {
		int rectLeft = squareX * 60 - 2;
		int rectTop = squareY * 60;
		if (this->bounds.intersects(sf::FloatRect(rectLeft, rectTop, 4, 60))) {
			return true;
		}
	}
	if (maze.wallRight(squareX, squareY, false)) {
		int rectLeft = squareX * 60 + 60 - 2;
		int rectTop = squareY * 60;
		if (this->bounds.intersects(sf::FloatRect(rectLeft, rectTop, 4, 60))) {
			return true;
		}
	}
	return false;
}
bool Player::collisionAt(double x, double y) {
	if (x <= 15) return true;
	if (x >= 600 - 15) return true;
	if (y <= 15) return true;
	if (y >= 600 - 15) return true;

	int squareX = (int)(x / 60);
	int squareY = (int)(y / 60);

	bounds.left = x - (30 / 2);
	bounds.top = y - (30 / 2);

	Maze maze = getMaze();

	if (collisionSquare(squareX, squareY)) { return true; }
	if (collisionSquare(squareX, squareY - 1)) { return true; }
	if (collisionSquare(squareX, squareY + 1)) { return true; }
	if (collisionSquare(squareX - 1, squareY)) { return true; }
	if (collisionSquare(squareX + 1, squareY)) { return true; }

	return false;
}
