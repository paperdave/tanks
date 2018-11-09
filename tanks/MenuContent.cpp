#include "pch.h"
#include "Menu.h"

void registerMainMenu() {
	Menu* menu = new Menu("main menu");
	menu->items.push_back(MenuItem("Quick Play", MenuItemTypeButton, "sub:quickplay"));
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

void registerAllMenus() {
	registerMainMenu();
	registerQuickPlayOptionsMenu();
}