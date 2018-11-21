#include "pch.h"
#include "Menu.h"
#include "Scene.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "Window.h"
#include "TankChooseMenuScene.h"

// Menus
void registerMainMenu() {
	Menu* menu = new Menu("main menu");
	menu->items.push_back(MenuItem("Quick Play", MenuItemTypeButton, "start"));
	menu->items.push_back(MenuItem("More Game Modes", MenuItemTypeButton, "sub:advanced"));
	menu->items.push_back(MenuItem(MenuItemTypeDivider));
	menu->items.push_back(MenuItem("Options", MenuItemTypeButton, "sub:options"));
	menu->items.push_back(MenuItem(MenuItemTypeDivider));
	menu->items.push_back(MenuItem("Exit", MenuItemTypeButton, "exit"));
	registerMenu("main", menu);
}

// Actions
void registerActions() {
	registerAction("start", [](MenuScene* menu) {
		setScene(new TankChooseMenuScene());
		//setScene(new GameScene(true,true,true,true, "menu"));
	});
	registerAction("menu", [](MenuScene* menu) {
		setScene(new MenuScene());
	});
	registerAction("exit", [](MenuScene* menu) {
		window.close();
	});
	registerAction("null", [](MenuScene* menu) {
		window.close();
	});
}

void registerAllMenus() {
	registerMainMenu();

	registerActions();
}