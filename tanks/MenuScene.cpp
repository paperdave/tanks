#include "pch.h"
#include "MenuScene.h"
#include "Menu.h"
#include "Utility.h"
#include "Resources.h"

MenuScene::MenuScene() {
	currentMenu = getMenu("main");
}

void MenuScene::update() {

	selectBoxTarget.top = 115;
	selectBoxTarget.left = 10;
	selectBoxTarget.width = 0;
	selectBoxTarget.height = 44;
	if (currentMenu) {
		int index = 0;
		for (auto item : currentMenu->items) {
			if (item.type == MenuItemTypeButton) {
				selectBoxTarget.top += 40;
				index++;
			}
			else if (item.type == MenuItemTypeDivider) {
				selectBoxTarget.top += 20;
			}
			if (selected + 1 == index) {
				break;
			}
		}
	}
	
	width = lerp(width, widthTarget, 0.1);

	selectBox.left = lerp(selectBox.left, selectBoxTarget.left, 0.5);
	selectBox.top = lerp(selectBox.top, selectBoxTarget.top, 0.5);
	selectBox.width = lerp(selectBox.width, selectBoxTarget.width, 0.5);
	selectBox.height = lerp(selectBox.height, selectBoxTarget.height, 0.5);
}

void MenuScene::render(sf::RenderTarget* g) {
	int offsetX = 640 - width / 2;

	sf::RectangleShape bg;
	bg.setFillColor(sf::Color(30, 30, 30));
	bg.setOutlineColor(sf::Color(10, 10, 10));
	bg.setOutlineThickness(10);
	bg.setSize(sf::Vector2f(width, 740));
	bg.setPosition(offsetX, -10);

	g->draw(bg);

	sf::RectangleShape select;
	select.setFillColor(sf::Color(70, 70, 70));
	select.setPosition(selectBox.left + offsetX, selectBox.top);
	select.setSize(sf::Vector2f(width - selectBox.left * 2, selectBox.height));

	g->draw(select);

	int y = 100;
	if (currentMenu) {

		sf::Text tx;
		tx.setFont(getFont("clean"));
		tx.setFillColor(sf::Color::White);
		tx.setString(currentMenu->title);
		tx.setCharacterSize(96);
		tx.setPosition(640, 10);
		tx.setOrigin(tx.getLocalBounds().width / 2, tx.getOrigin().y);
		g->draw(tx);

		for (auto item : currentMenu->items) {
			if (item.type == MenuItemTypeButton) {
				y += 40;
				sf::Text tx;
				tx.setFont(getFont("clean"));
				tx.setFillColor(sf::Color::White);
				tx.setString(item.label);
				tx.setCharacterSize(48);
				tx.setPosition(offsetX + 10, y);
				g->draw(tx);
			}
			else if (item.type == MenuItemTypeDivider) {
				y += 20;
			}
			else if (item.type == MenuItemTypeLabel) {
				printf("Error: Menu type Label not implemented");
				throw "MenuError";
			}
		}
	}
}

void MenuScene::event_onKeyPress(sf::Event::KeyEvent event) {
	if (event.code == sf::Keyboard::Up) {
		selected--;
	}
	else if (event.code == sf::Keyboard::Down) {
		selected++;
	}
	else if (event.code == sf::Keyboard::Space) {
		int index = 0;
		for (auto item : currentMenu->items) {
			if (item.type == MenuItemTypeButton) {
				index++;
			}
			if (selected + 1 == index) {
				executeAction(item.target);
				break;
			}
		}
	}
}
void MenuScene::event_onKeyRelease(sf::Event::KeyEvent event) {

}
