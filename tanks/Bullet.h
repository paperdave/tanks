#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
	double speed = 4.5;
	double mx = 0;
	double my = 0;
	double x = 30;
	double y = 30;
	double dir = 90;
	int collisionComboX = 0;
	int collisionComboY = 0;
	int life = 60 * 7.5;
	
	int collisionAt(double x, double y, Maze maze);
	int collisionSquare(int squareX, int squareY, Maze maze);

public:
	int beforeTime = 5;

	Bullet(double x, double y, double direction);
	~Bullet();

	virtual void update();
	virtual void render(sf::RenderTarget* g);
};

