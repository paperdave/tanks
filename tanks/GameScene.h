#pragma once
#include "Scene.h"
#include "Maze.h"

class GameScene :
	public Scene
{
private:
	sf::RenderTexture shadowSurface;
	Maze maze;
public:
	GameScene();

	void render(sf::RenderTarget* g);
};

