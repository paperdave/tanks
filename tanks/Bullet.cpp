#include "pch.h"
#include "Bullet.h"
#include "Resources.h"
#include "Utility.h"

int Bullet::collisionSquare(int squareX, int squareY, Maze maze) {
	if (maze.wallDown(squareX, squareY, false)) {
		int rectLeft = squareX * 60;
		int rectTop = squareY * 60 + 60 - 2;
		if (bounds.intersects(sf::FloatRect(rectLeft, rectTop, 60, 2))) {
			return 2;
		}
	}
	if (maze.wallUp(squareX, squareY, false)) {
		int rectLeft = squareX * 60;
		int rectTop = squareY * 60 - 2;
		if (bounds.intersects(sf::FloatRect(rectLeft, rectTop, 60, 2))) {
			return 2;
		}
	}
	if (maze.wallLeft(squareX, squareY, false)) {
		int rectLeft = squareX * 60 - 2;
		int rectTop = squareY * 60;
		if (bounds.intersects(sf::FloatRect(rectLeft, rectTop, 2, 60))) {
			return 1;
		}
	}
	if (maze.wallRight(squareX, squareY, false)) {
		int rectLeft = squareX * 60 + 60 - 2;
		int rectTop = squareY * 60;
		if (bounds.intersects(sf::FloatRect(rectLeft, rectTop, 2, 60))) {
			return 1;
		}
	}
	return false;
}
int Bullet::collisionAt(double x, double y, Maze maze) {
	int squareX = (int)(x / 60);
	int squareY = (int)(y / 60);

	bounds.left = x - (bounds.width / 2);
	bounds.top = y - (bounds.height / 2);

	int r = 0;
	if (r = collisionSquare(squareX, squareY, maze)) { return r; }
	if (r = collisionSquare(squareX, squareY - 1, maze)) { return r; }
	if (r = collisionSquare(squareX, squareY + 1, maze)) { return r; }
	if (r = collisionSquare(squareX - 1, squareY, maze)) { return r; }
	if (r = collisionSquare(squareX + 1, squareY, maze)) { return r; }

	return false;
}

Bullet::Bullet(double x, double y, double direction, float speed) {
	type = GameObjectType::BulletType;
	
	this->x = x;
	this->y = y;
	this->dir = direction + (((float)(rand() % 10)) / 5.0f) - 1.0f;
	this->mx = lengthdir_x(speed, this->dir);
	this->my = lengthdir_y(speed, this->dir);
	this->bounds.width = 10;
	this->bounds.height = 10;
}
Bullet::~Bullet() {

}

void Bullet::update() {
	if (beforeTime > -1) beforeTime--;
	int bbox = (bounds.height / 2);

	bounds.left = x - (bounds.width / 2);
	bounds.top = y - (bounds.height / 2);

	double moveX = mx;
	double moveY = my;

	y += moveY;
	x += moveX;

	int cat = collisionAt(x, y, getMaze());

	if (x <= bbox || x >= 600 - bbox || cat == 1) {
		mx *= -1;
		collisionComboX++;
		if (collisionComboX == 2) {
			my *= -1;
			mx *= -1;
			y += mx;
			x += my;

		}
	}
	else {
		this->collisionComboX = 0;
	}
	
	if (y <= bbox || y >= 600 - bbox || cat == 2) {
		my *= -1;
		collisionComboY++;
		if (collisionComboY == 2) {
			my *= -1;
			mx *= -1;
			y += mx;
			x += my;
			y += mx;
			x += my;

		}
	}
	else {
		this->collisionComboY = 0;
	}
	life--;
	if (life <= 0) {
		destroySelf();
	}
}

void Bullet::render(sf::RenderTarget* g) {
	sf::Sprite s;
	s.setTexture(getTexture("bullet/basic"));
	s.setPosition(this->x, this->y);
	s.setScale(0.6f, 0.6f);
	s.setOrigin(s.getLocalBounds().width / 2, s.getLocalBounds().height / 2);

	g->draw(s);
}