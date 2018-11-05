#pragma once
#include "Scene.h"
class MenuScene : public Scene {
private:
	int shadowOpacity = 0;
	int bgOpacity = 255;
	double scale = 5;
	int delay = 30;
public:
	MenuScene();

	void render(sf::RenderTarget* g);
	void update();
};

