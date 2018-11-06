#pragma once
#include "Scene.h"
#include "Maze.h"
#include "GameObject.h"
#include <deque>
#include <SFML/Graphics.hpp>

class GameObject;

class GameScene :
	public Scene
{
private:
	sf::RenderTexture wallSideSurface;
	sf::RenderTexture wallSurface;
public:
	GameScene();

	virtual void render(sf::RenderTarget* g);
	virtual void update();
	virtual void event_onKeyPress(sf::Event::KeyEvent event);
	virtual void event_onKeyRelease(sf::Event::KeyEvent event);
	
	Maze maze;
	std::deque<GameObject*> objects;
};

