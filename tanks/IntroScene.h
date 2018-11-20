#pragma once
#include "Scene.h"
class IntroScene : public Scene {
private:
	int shadowOpacity = 0;
	int bgOpacity = 255;
	double scale = 5;
	int delay = 30;
	int initDelay = 19;
public:
	IntroScene();

	virtual void event_onKeyPress(sf::Event::KeyEvent);

	void render(sf::RenderTarget* g);
	void update();
};

