#include "pch.h"
#include "Player.h"
#include "Utility.h"
#include "Resources.h"

Player::Player(sf::Vector2i position, int playerID) {
	hue = hue;

	controls = getPlayerControlsByID(playerID);
	dir = rand() % 360;
	x = 60 * (position.x) + 30;
	y = 60 * (position.y) + 30;
	bounds.width = 30;
	bounds.height = 30;
	id = playerID;

	turnSpeed = 1;
	speed = 1;
}

void Player::HandleKeypress(int code, bool state) {
	printf("%d\n", code);
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

	x += move_x;
	y += move_y;
}

void Player::render(sf::RenderTarget* g) {
	sf::Texture &texTop = getTexture("tank-1");
	sf::Sprite sTop;

	int sat = wave(255, 0, 0.8, 0);
	this->gunOffset *= 0.5;

	sTop.setTexture(texTop);
	sTop.setScale(0.7, 0.7);
	sTop.setOrigin(sTop.getLocalBounds().width / 2 * 0.8, sTop.getLocalBounds().height / 2);

	sTop.setRotation(dir);
	sTop.setColor(sf::Color::Red);

	sTop.setPosition(x, y);

	sf::Texture &texBot = getTexture("tank-tip");
	sf::Sprite sBot;

	sBot.setTexture(texBot);
	sBot.setScale(0.7, 0.7);
	sBot.setOrigin(sTop.getOrigin());

	sBot.setRotation(dir);
	sBot.setColor(sf::Color::Red);

	sBot.setPosition(x + lengthdir_x(-gunOffset, (double)dir), y + lengthdir_y(-gunOffset, dir) - 4);

	g->draw(sTop);
	
	sTop.move(0, -1);
	g->draw(sTop);
	sTop.move(0, -1);
	g->draw(sTop);
	sTop.move(0, -1);
	g->draw(sTop);
	sTop.move(0, -1);
	g->draw(sTop);

	g->draw(sBot);
	sBot.move(0, -1);
	g->draw(sBot);
	sBot.move(0, -1);
	g->draw(sBot);

}