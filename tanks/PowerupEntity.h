#pragma 
#include "GameObject.h"
#include "Powerup.h"
#include "SFML/Graphics.hpp"

class PowerupEntity : public GameObject {
public:
	PowerupEntity(int gridx, int gridy, PowerupType type);
	~PowerupEntity();

	int x;
	int y;
	int z = 1000;
	int beamwidth = 60;
	PowerupType powerupType;
	float angle = 0;

	virtual void update();
	virtual void render(sf::RenderTarget* g);
};

