#pragma once
#include "Scene.h"
#include "Player.h"

class PreviewExpiredScene : public Scene {
private:
	Player* playerDummy;
public:
	PreviewExpiredScene();

	void render(sf::RenderTarget* g);
	void update();
};

