#pragma once
#include "SFML/Graphics.hpp"
class BackgroundScene {
private:
	sf::Sprite bg;
	int background_size;
	float bg_offset = 1;
public:
	BackgroundScene();
	virtual void render(sf::RenderTarget* g);
	void update();
};

