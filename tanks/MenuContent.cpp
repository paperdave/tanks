#include "pch.h"
#include "Menu.h"
#include "Scene.h"
#include "GameScene.h"

// Menus
void registerMainMenu() {
	Menu* menu = new Menu("main menu");
	menu->items.push_back(MenuItem("Quick Play", MenuItemTypeButton, "quick-play-options"));
	menu->items.push_back(MenuItem(MenuItemTypeDivider));
	menu->items.push_back(MenuItem("item 3", MenuItemTypeButton, "testAction1"));
	menu->items.push_back(MenuItem("item 4", MenuItemTypeButton, "testAction2"));
	menu->items.push_back(MenuItem("item 5", MenuItemTypeButton, "testAction3"));
	registerMenu("main", menu);
}
void registerQuickPlayOptionsMenu() {
	Menu* menu = new Menu("submenu");
	menu->items.push_back(MenuItem("Sub Menu", MenuItemTypeButton, "none"));
	menu->items.push_back(MenuItem("It's Very", MenuItemTypeButton, "none"));
	menu->items.push_back(MenuItem("Cool", MenuItemTypeButton, "none"));
	registerMenu("test1", menu);
}

// Actions
void action_startGame() {
	setScene(new GameScene());
}

void registerAllMenus() {
	registerMainMenu();
	registerQuickPlayOptionsMenu();

	registerAction("start-game", action_startGame);
}