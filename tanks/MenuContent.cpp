#include "pch.h"
#include "Menu.h"
#include "Scene.h"
#include "MenuScene.h"

// Menus
void registerMainMenu() {
	Menu* menu = new Menu("main menu");
	menu->items.push_back(MenuItem("Quick Play", MenuItemTypeButton, "sub:quick-play"));
	menu->items.push_back(MenuItem("Quick Play", MenuItemTypeButton, "sub:quick-play"));
	menu->items.push_back(MenuItem(MenuItemTypeDivider));
	menu->items.push_back(MenuItem("item 3", MenuItemTypeButton, "testAction1"));
	menu->items.push_back(MenuItem("item 4", MenuItemTypeButton, "testAction2"));
	menu->items.push_back(MenuItem("item 5", MenuItemTypeButton, "menu:quick-play"));
	registerMenu("main", menu);
}
void registerQuickPlayOptionsMenu() {
	Menu* menu = new Menu("submenu");
	menu->items.push_back(MenuItem("Sub Menu", MenuItemTypeButton, "none"));
	menu->items.push_back(MenuItem("It's Very", MenuItemTypeButton, "none"));
	menu->items.push_back(MenuItem("Cool", MenuItemTypeButton, "close-sub"));
	registerMenu("quick-play", menu);
}

// Actions
void registerActions() {
	registerAction("close-sub", [](MenuScene* menu) {
		menu->setSubMenu(nullptr);
	});
}

void registerAllMenus() {
	registerMainMenu();
	registerQuickPlayOptionsMenu();

	registerActions();
	
}