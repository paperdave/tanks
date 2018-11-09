#include "pch.h"
#include "MenuScene.h"
#include "Menu.h"
#include "Resources.h"

MenuScene::MenuScene() {
	currentMenu = getMenu("main");
}

void MenuScene::render(sf::RenderTarget* g) {
	sf::RectangleShape bg;
	bg.setFillColor(sf::Color(30, 30, 30));
	bg.setOutlineColor(sf::Color(20, 20, 20));
	bg.setOutlineThickness(4);
	bg.setSize(sf::Vector2f(400, 500));
	bg.setPosition(100, 50);
	
	g->draw(bg);

	int y = 0;
	if (currentMenu) {

		for (auto item : currentMenu->items) {
			if (item.type == MenuItemTypeButton) {
				y += 32;
				sf::Text tx;
				tx.setFont(getFont("clean"));
				tx.setFillColor(sf::Color::White);
				tx.setString(item.label);
				tx.setCharacterSize(24);
				tx.setPosition(100, y);
				g->draw(tx);
			}
			else if (item.type == MenuItemTypeDivider) {
				y+=20
			}
			else if (item.type == MenuItemTypeLabel) {
				printf("Error: Menu type Label not implemented");
				throw "MenuError";
			}
		}
	}

}

void MenuScene::update() {

}
