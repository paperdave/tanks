#include "Powerup.h"
#include "pch.h"


Powerup::Powerup()
{
}


Powerup::~Powerup()
{
}

sf::Color getPowerupColor(PowerupType type) {
	switch (type) {
	case PowerupTypeSpeed: return sf::Color(0, 255, 255);
	case PowerupTypeRapidFire: return sf::Color(255, 0, 255);

	default: return sf::Color::White;
	}
}