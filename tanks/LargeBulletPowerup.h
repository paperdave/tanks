#pragma once
#include "Powerup.h"
class LargeBulletPowerup :
	public Powerup
{
public:
	LargeBulletPowerup();
	~LargeBulletPowerup();

	void activate();
	void deactivate();
	virtual void render(sf::RenderTarget *g);
	virtual void update();
};

