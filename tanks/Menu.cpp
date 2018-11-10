#include "Menu.h"

namespace {
	std::map<std::string, Menu*> menuRegistry;
	std::map<std::string, ActionCallback> actionRegistry;
}

void registerMenu(std::string name, Menu* menu) {
	printf("Registering Menu %s\n", name.c_str());
	menuRegistry.insert(std::make_pair(name, menu));
}
void registerAction(std::string name, ActionCallback func) {
	printf("Registering Action %s\n", name.c_str());
	actionRegistry.insert(std::make_pair(name, func));
}

Menu* getMenu(std::string name) {
	std::map<std::string, Menu*>::iterator itr = menuRegistry.find(name);
	if (itr == menuRegistry.end()) {
		printf("Menu not found: %s\n", name.c_str());
		throw "Menu Not Found";
	}
	else {
		return itr->second;
	}
}

void executeAction(std::string name) {
	std::map<std::string, ActionCallback>::iterator itr = actionRegistry.find(name);
	if (itr == actionRegistry.end()) {
		printf("WARN: Action not '%s' not found\n");
	}
	else {
		(*itr->second)();
	}
}