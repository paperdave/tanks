#include "pch.h"
#include "MenuScene.h"
#include "Resources.h"

MenuScene::MenuScene() {
	
}

void MenuScene::render(sf::RenderTarget* g) {
	sf::RectangleShape bg;
	bg.setFillColor(sf::Color(30, 30, 30));
	bg.setOutlineColor(sf::Color(20, 20, 20));
	bg.setOutlineThickness(4);
	bg.setSize(sf::Vector2f(400, 500));
	bg.setPosition(100, 50);

	sf::Text tx;
	tx.setFont(getFont("clean"));
	tx.setFillColor(sf::Color::White);
	tx.setString("oof");
	tx.setCharacterSize(24);

	g->draw(bg);
	g->draw(tx);
}

void MenuScene::update() {

}