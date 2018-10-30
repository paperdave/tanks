#include "pch.h"
#include "BackgroundScene.h"
#include "Resources.h"

BackgroundScene::BackgroundScene() {
	printf("constructor\n");
	bg.setTexture(getTexture("background"));
	bg.setScale(0.5, 0.5);
	background_size = getTexture("background").getSize().x * bg.getScale().x;
}

void BackgroundScene::render(sf::RenderTarget* g) {
	// Move BG
	bg_offset = (bg_offset + 0.1);
	if (bg_offset >= background_size) bg_offset -= background_size;

	// Draw BG
	for (float xx = bg_offset; xx < g->getSize().x + background_size + 32; xx += background_size) {
		for (float yy = 0; yy < g->getSize().y + background_size; yy += background_size) {
			bg.setPosition(sf::Vector2f(xx - background_size, yy));
			g->draw(bg);
		}
	}
}