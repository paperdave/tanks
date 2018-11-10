#pragma once
#include "Maze.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Light : public GameObject {
public:
	sf::Color color;
	int startx;
	int starty;
	int visitedmap[10][10];
	Light(sf::Color c, int x, int y);
	~Light();

	void update();
	void drawSquare(int posx, int posy, float opacity);
	void render(sf::RenderTarget* g);
};