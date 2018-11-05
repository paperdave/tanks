#include "pch.h"
#include "Bullet.h"
#include "Resources.h"
#include "Utility.h"

Bullet::Bullet(double x, double y, double direction) {
	this->x = x;
	this->y = y;
	this->dir = direction + (((float)(rand() % 10)) / 5.0f) - 1.0f;
	this->mx = lengthdir_x(this->speed, this->dir);
	this->my = lengthdir_y(this->speed, this->dir);
	this->bounds.width = 10;
	this->bounds.height = 10;
}

void Bullet::update() {

}

void Bullet::render(sf::RenderTarget* g) {
	sf::Sprite s;
	s.setTexture(getTexture("bullet/basic"));
	s.setPosition(this->x, this->y);
	s.setScale(0.6, 0.6);
	s.setOrigin(s.getLocalBounds().width / 2, s.getLocalBounds().height / 2);

	g->draw(s);
}