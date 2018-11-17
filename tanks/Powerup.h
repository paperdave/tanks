#pragma once
#include "SFML/Graphics.hpp"

class Player;

class Powerup {
public:
	Powerup();
	~Powerup();

	bool active = true;

	Player* player;

	virtual void activate() = 0;
	virtual void deactivate() = 0;
	virtual void render(sf::RenderTarget *g) {};
	virtual void update() {};
};

enum PowerupType {
	PowerupTypeSpeed
};