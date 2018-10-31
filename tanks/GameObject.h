#pragma once
#include "SFML/Graphics.hpp"
class GameObject
{
public:
	GameObject();

	virtual void tick(sf::RenderTexture* g) = 0;
	virtual void render(sf::RenderTexture* g) = 0;
};

