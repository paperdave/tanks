#pragma once
#include "Powerup.h"
class SpeedPowerup : public Powerup {
public:
	SpeedPowerup();
	~SpeedPowerup();

	int timer = 60 * 10;

	void activate();
	void deactivate();
	virtual void render(sf::RenderTarget *g);
	virtual void update();
};

