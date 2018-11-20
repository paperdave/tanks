#include "pch.h"
#include "MenuScene.h"
#include "Menu.h"
#include "Utility.h"
#include "Resources.h"

MenuScene::MenuScene() {
	currentMenu = getMenu("main");
	escapeAction = "exit";
}

void MenuScene::update() {

	selectBoxTarget.top = 115;
	selectBoxTarget.left = (currentSubMenu != nullptr) ? 0 : 10;
	selectBoxTarget.height = 44;
	int index = 0;
	if (selected < 0) selected = 0;
	for (auto item : currentMenu->items) {
		// Increase index on selectable items.
		if (item.type == MenuItemTypeButton) {
			index++;
		}
		
		// Move Main Menu Selection Box
		if (item.type == MenuItemTypeButton) {
			selectBoxTarget.top += 40;
		}
		else if (item.type == MenuItemTypeDivider) {
			selectBoxTarget.top += 20;
		}

		// If we selected this, box is done!
		if (selected + 1 == index) {
			break;
		}
	}
	
	width = lerp(width, widthTarget, 0.1);

	selectBox.left = lerp(selectBox.left, selectBoxTarget.left, 0.2);
	selectBox.top = lerp(selectBox.top, selectBoxTarget.top, 0.35);
	selectBox.height = lerp(selectBox.height, selectBoxTarget.height, 0.35);
}

void MenuScene::render(sf::RenderTarget* g) {
	int offsetX = (g->getSize().x / 2) - width / 2;

	sf::RectangleShape bg;
	bg.setFillColor(sf::Color(30, 30, 30));
	bg.setOutlineColor(sf::Color(10, 10, 10));
	bg.setOutlineThickness(10);
	bg.setSize(sf::Vector2f(width, g->getSize().y + 20));
	bg.setPosition(offsetX, -10);

	g->draw(bg);

	sf::RectangleShape select;
	select.setFillColor(sf::Color(70, 70, 70));
	select.setPosition(selectBox.left + offsetX, selectBox.top);
	select.setSize(sf::Vector2f(width - selectBox.left * 2, selectBox.height));

	g->draw(select);

	int y = 100;

	sf::Text tx;
	tx.setFont(getFont("clean"));
	tx.setFillColor(sf::Color::White);
	tx.setString(currentMenu->title);
	tx.setCharacterSize(96);
	tx.setPosition(g->getSize().x/2, 10);
	tx.setOrigin(tx.getLocalBounds().width / 2, tx.getOrigin().y);
	g->draw(tx);
	int index = -1;
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
			index++;
		}
		else if (item.type == MenuItemTypeDivider) {
			y += 20;
		}
		else if (item.type == MenuItemTypeLabel) {
			LOG("Error: Menu type Label not implemented");
			throw "MenuError";
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
	else if (event.code == sf::Keyboard::Space || event.code == sf::Keyboard::Enter) {
		int index = 0;
		for (auto item : currentMenu->items) {
			if (item.type == MenuItemTypeButton) {
				index++;
			}
			if (selected + 1 == index) {
				executeAction(item.target, this);
				break;
			}
		}
	}
	else if (event.code == sf::Keyboard::Escape) {
		setSubMenu(nullptr);
	}
}
void MenuScene::event_onKeyRelease(sf::Event::KeyEvent event) {

}

void MenuScene::setMenu(Menu* newMenu, int defaultPos) {
	currentMenu = newMenu;
	selected = defaultPos;
}
void MenuScene::setSubMenu(Menu* newMenu) {
	// TODO: Reimplement
}