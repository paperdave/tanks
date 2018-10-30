#pragma once
#include "Scene.h"
class GameScene :
	public Scene
{
private:
	sf::RenderTexture shadowSurface;
public:
	GameScene();

	void render(sf::RenderTarget* g);
};

