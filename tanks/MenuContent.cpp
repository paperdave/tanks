#include "pch.h"
#include "Menu.h"
#include "Scene.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "Resources.h"
#include "Window.h"
#include "Transition.h"
#include "TankChooseMenuScene.h"

// Menus
void registerMainMenu() {
	Menu* menu = new Menu("main menu");
	menu->items.push_back(MenuItem("Quick Play", MenuItemTypeButton, "quick-play"));
	menu->items.push_back(MenuItem("More Game Modes", MenuItemTypeLabel, "sub:advanced"));
	menu->items.push_back(MenuItem(MenuItemTypeDivider));
	menu->items.push_back(MenuItem("Options", MenuItemTypeButton, "sub:options"));
	menu->items.push_back(MenuItem(MenuItemTypeDivider));
	menu->items.push_back(MenuItem("Exit", MenuItemTypeButton, "exit"));
	registerMenu("main", menu);
}
void registerOptionsMenu() {
	Menu* menu = new Menu("Options");
	menu->items.push_back(MenuItem("Back", MenuItemTypeButton, "close-sub"));
	menu->items.push_back(MenuItem(MenuItemTypeDivider));
	menu->items.push_back(MenuItem("Fullscreen", MenuItemTypeToggle, "fullscreen"));
	menu->items.push_back(MenuItem("FPS", MenuItemTypeToggle, "fps"));
	menu->items.push_back(MenuItem("Sounds", MenuItemTypeToggle, "audio"));
	registerMenu("options", menu);
}
void registerAdvancedMenu() {
	Menu* menu = new Menu("Advanced");
	menu->items.push_back(MenuItem("Back", MenuItemTypeButton, "close-sub"));
	menu->items.push_back(MenuItem(MenuItemTypeDivider));
	menu->items.push_back(MenuItem("Speed Powerup", MenuItemTypeButton, "null"));
	menu->items.push_back(MenuItem("Rapid Fire Powerup", MenuItemTypeButton, "null"));
	menu->items.push_back(MenuItem("Large Bullet Powerup", MenuItemTypeButton, "null"));
	menu->items.push_back(MenuItem(MenuItemTypeDivider));
	menu->items.push_back(MenuItem("PLAY", MenuItemTypeButton, "start-advanced-game"));
	registerMenu("advanced", menu);
}
// Actions
void registerActions() {
	
	// Quick Play
	registerAction("quick-play", [](MenuScene* menu) {
		menu->tcms = new TankChooseMenuScene("quick-play-transition", "Quick Play", 1);
		menu->closing = true;
	});
	registerAction("quick-play-transition", [](MenuScene* menu) {
		setScene(new Transition(new TankChooseMenuScene("quick-play-transition", "Quick Play")));
	});


	// Misc
	registerAction("menu", [](MenuScene* menu) {
		setScene(new MenuScene());
	});
	registerAction("close-sub", [](MenuScene* menu) {
		menu->closing = true;
		playSound("menu/deactivate");
	});
	registerAction("exit", [](MenuScene* menu) {
		window.close();
	});
	registerAction("null", [](MenuScene* menu) {
		LOG("WARN: `null` action used.\n");
	});
}

void registerAllMenus() {
	registerMainMenu();
	registerOptionsMenu();
	registerAdvancedMenu();

	registerActions();
}