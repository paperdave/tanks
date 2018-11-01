#pragma once
#include "Scene.h"
#include "Maze.h"
#include "GameObject.h"
#include "Player.h"
#include <deque>

class GameScene :
	public Scene
{
private:
	sf::RenderTexture shadowSurface;
	std::deque<GameObject> objects;
	Player* player;
	Maze maze;
public:
	GameScene();

	virtual void render(sf::RenderTarget* g);
	virtual void update();
	virtual void event_onKeyPress(sf::Event::KeyEvent event);
	virtual void event_onKeyRelease(sf::Event::KeyEvent event);
};

