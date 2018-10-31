#include "pch.h"
#include "BackgroundScene.h"
#include "Resources.h"

BackgroundScene::BackgroundScene() {
	bg.setTexture(getTexture("background"));
	bg.setScale(0.5, 0.5);
	background_size = getTexture("background").getSize().x * bg.getScale().x;
}

void BackgroundScene::update() {
	// Move BG
	bg_offset = (bg_offset + 0.1f);
	if (bg_offset >= background_size) bg_offset -= background_size;
}

void BackgroundScene::render(sf::RenderTarget* g) {
	// Draw BG
	for (double xx = bg_offset; xx < g->getSize().x + background_size + 32; xx += background_size) {
		for (double yy = 0; yy < g->getSize().y + background_size; yy += background_size) {
			bg.setPosition(sf::Vector2f(xx - background_size, yy));
			g->draw(bg);
		}
	}
}