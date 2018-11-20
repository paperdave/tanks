#include "Menu.h"
#include "MenuScene.h"
#include "pch.h"

namespace {
	std::map<std::string, Menu*> menuRegistry;
	std::map<std::string, ActionCallback> actionRegistry;
}

void registerMenu(std::string name, Menu* menu) {
	// Register
	LOG("Registering Menu %s\n", name.c_str());
	menuRegistry.insert(std::make_pair(name, menu));

	// Handler for switching to it
	registerAction("menu:" + name, [name](MenuScene* menu) {
		menu->setMenu(getMenu(name));
	});
	registerAction("sub:" + name, [name](MenuScene* menu) {
		menu->setSubMenu(getMenu(name));
	});
}
void registerAction(std::string name, ActionCallback func) {
	LOG("Registering Action %s\n", name.c_str());
	actionRegistry.insert(std::make_pair(name, func));
}

Menu* getMenu(std::string name) {
	std::map<std::string, Menu*>::iterator itr = menuRegistry.find(name);
	if (itr == menuRegistry.end()) {
		LOG("Menu not found: %s\n", name.c_str());
		throw "Menu Not Found";
	}
	else {
		return itr->second;
	}
}

void executeAction(std::string name, MenuScene* menu) {
	std::map<std::string, ActionCallback>::iterator itr = actionRegistry.find(name);
	if (itr == actionRegistry.end()) {
		LOG("WARN: Action not '%s' not found\n", name.c_str());
	}
	else {
		(itr->second)(menu);
	}
}