#include "pch.h"
#include "Menu.h"
#include "Scene.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "Window.h"

// Menus
void registerMainMenu() {
	Menu* menu = new Menu("main menu");
	menu->items.push_back(MenuItem("Quick Play Menu", MenuItemTypeButton, "sub:quick-play"));
	menu->items.push_back(MenuItem("Goto Game", MenuItemTypeButton, "start"));
	menu->items.push_back(MenuItem("Exit", MenuItemTypeButton, "exit"));
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
	registerAction("start", [](MenuScene* menu) {
		setScene(new GameScene());
	});
	registerAction("exit", [](MenuScene* menu) {
		window.close();
	});
}

void registerAllMenus() {
	registerMainMenu();
	registerQuickPlayOptionsMenu();

	registerActions();
}