#pragma once
#include "SFML/Graphics.hpp"

class Scene
{
public:
	Scene();
	// Required Render Function
	virtual void render(sf::RenderTarget* g) = 0;
	virtual void update() = 0;

	// Event Handlers
	virtual void event_onKeyPress(sf::Event::KeyEvent event) {};
	virtual void event_onKeyRelease(sf::Event::KeyEvent event) {};
};

extern Scene* currentScene;
