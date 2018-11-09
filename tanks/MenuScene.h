#pragma once
#include "Scene.h"
#include "Menu.h"

class MenuScene : public Scene {
private:
	Menu* currentMenu;
	int selected = 0;

public:
	MenuScene();
	
	void render(sf::RenderTarget* g);
	void update();
};

