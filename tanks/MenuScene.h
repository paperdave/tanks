#pragma once
#include "Scene.h"
class MenuScene :
	public Scene
{
public:
	MenuScene();
	
	void render(sf::RenderTarget* g);
	void update();
};

