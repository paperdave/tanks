#pragma once
#include "Powerup.h"
class RapidFirePowerup :
	public Powerup
{
public:
	RapidFirePowerup();
	~RapidFirePowerup();

	int timer = 60 * 5.5;

	void activate();
	void deactivate();
	virtual void render(sf::RenderTarget *g);
	virtual void update();
};

