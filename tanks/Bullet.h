#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:
	double mx = 0;
	double my = 0;
	double x = 30;
	double y = 30;
	double dir = 90;
	int collisionComboX = 0;
	int collisionComboY = 0;
	int life = (int)(60.0 * 7.5);
	
	int collisionAt(double x, double y, Maze maze);
	int collisionSquare(int squareX, int squareY, Maze maze);

	int beforeTime = 5;

	Bullet(double x, double y, double direction, float speed);
	~Bullet();

	virtual void update();
	virtual void render(sf::RenderTarget* g);
};
