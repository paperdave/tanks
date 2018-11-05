#pragma once
#include "SFML/Graphics.hpp"
#include "Maze.h"
#include "GameScene.h"
 
class GameScene;

class GameObject
{
public:
	GameObject();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* g) = 0;

	// Event Handlers
	virtual void event_onKeyPress(sf::Event::KeyEvent event) {};
	virtual void event_onKeyRelease(sf::Event::KeyEvent event) {};

	GameScene* scene = nullptr;

	Maze getMaze();
	void createObject(GameObject* obj);
	void destroySelf();
};

