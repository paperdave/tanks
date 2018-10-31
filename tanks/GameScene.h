#pragma once
#include "Scene.h"
#include "Maze.h"
#include "GameObject.h"
#include <deque>

class GameScene :
	public Scene
{
private:
	sf::RenderTexture shadowSurface;
	Maze maze;
	std::deque<GameObject> objects;
public:
	GameScene();

	void render(sf::RenderTarget* g);
	void update();
};

