#pragma once
#include "Scene.h"
#include "Menu.h"
#include "SFML/Graphics.hpp"

class MenuScene : public Scene {
private:
	Menu* currentMenu;
	int selected = 0;

	int width = 500;

	float yOffset = 1;
	float titleImageY = 1;

	sf::IntRect selectBoxTarget;
	sf::IntRect selectBox;

	MenuScene* sub;
	int level;

public:
	MenuScene(std::string menuID, int level = 0);
	MenuScene();
	
	void render(sf::RenderTarget* g);
	void update();

	virtual void event_onKeyPress(sf::Event::KeyEvent event);
	virtual void event_onKeyRelease(sf::Event::KeyEvent event);

	void setMenu(Menu* newMenu, int defaultPos = 0);
	void setSubMenu(std::string newMenu);

	bool closing = false;
};
