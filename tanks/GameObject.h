#pragma once
#include "SFML/Graphics.hpp"
class GameObject
{
public:
	GameObject();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* g) = 0;
};

