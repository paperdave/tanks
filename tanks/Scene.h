#pragma once
#include "SFML/Graphics.hpp"

extern float shakeRemain;
extern float shakeMagnitude;
extern float shakeLength;

class Scene {
public:
	Scene();
	virtual ~Scene();
	// Required Render Function
	virtual void render(sf::RenderTarget* g) = 0;
	virtual void update() = 0;

	// Event Handlers
	virtual void event_onKeyPress(sf::Event::KeyEvent event) {};
	virtual void event_onKeyRelease(sf::Event::KeyEvent event) {};
};

void setScene(Scene* newScene);
void screenShake(float magnitude, int frames);

extern Scene* currentScene;
extern Scene* nextScene;
