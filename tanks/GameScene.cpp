#include "pch.h"
#include "GameScene.h"
#include "SFML/Graphics.hpp"


GameScene::GameScene() {
	this->shadowSurface.create(600, 600);
}

void GameScene::render(sf::RenderTarget* g) {
	// move the view so the 600x600 area is the center
	sf::View view = g->getView();
	view.move(-340, -60);
	g->setView(view);

	this->shadowSurface.clear(sf::Color::Transparent);
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(229, 229, 229, 255));
	rect.setOutlineColor(sf::Color(0, 0, 0, 255));
	rect.setOutlineThickness(4);
	rect.setPosition(0, 0);
	rect.setSize(sf::Vector2f(600, 600));

	g->draw(rect);
}