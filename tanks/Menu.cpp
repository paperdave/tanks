#include "Menu.h"
#include "MenuScene.h"

namespace {
	std::map<std::string, Menu*> menuRegistry;
	std::map<std::string, ActionCallback> actionRegistry;
}

void registerMenu(std::string name, Menu* menu) {
	// Register
#if PRINTF_ENABLE
	printf("Registering Menu %s\n", name.c_str());
#endif
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
#if PRINTF_ENABLE
	printf("Registering Action %s\n", name.c_str());
#endif
	actionRegistry.insert(std::make_pair(name, func));
}

Menu* getMenu(std::string name) {
	std::map<std::string, Menu*>::iterator itr = menuRegistry.find(name);
	if (itr == menuRegistry.end()) {
#if PRINTF_ENABLE
		printf("Menu not found: %s\n", name.c_str());
#endif
		throw "Menu Not Found";
	}
	else {
		return itr->second;
	}
}

void executeAction(std::string name, MenuScene* menu) {
	std::map<std::string, ActionCallback>::iterator itr = actionRegistry.find(name);
	if (itr == actionRegistry.end()) {
#if PRINTF_ENABLE
		printf("WARN: Action not '%s' not found\n", name.c_str());
#endif
	}
	else {
		(itr->second)(menu);
	}
}