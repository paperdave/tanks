#pragma once
#include "Scene.h"
class Transition : public Scene {
private:
	Scene* scene;
	double y = 1000;
	float zoom = 0.5;
public:
	Transition(Scene* scene);

	void render(sf::RenderTarget* g);
	void update();

	virtual void event_onKeyPress(sf::Event::KeyEvent event);
	virtual void event_onKeyRelease(sf::Event::KeyEvent event);
};

