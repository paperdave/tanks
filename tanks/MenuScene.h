#pragma once
#include "Scene.h"
#include "Menu.h"
#include "SFML/Graphics.hpp"

class MenuScene : public Scene {
private:
	Menu* currentMenu;
	int selected = 0;

	int width = 1280;
	int widthTarget = 450;

	sf::IntRect selectBoxTarget;
	sf::IntRect selectBox;

public:
	MenuScene();
	
	void render(sf::RenderTarget* g);
	void update();

	virtual void event_onKeyPress(sf::Event::KeyEvent event);
	virtual void event_onKeyRelease(sf::Event::KeyEvent event);

	void setMenu(Menu* newMenu, int defaultPos = 0);
	void openSubMenu(Menu* newMenu);
};
