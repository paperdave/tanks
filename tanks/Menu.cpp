#include "Menu.h"

namespace {
	std::map<std::string, Menu*> menuRegistry;
}

void registerMenu(std::string name, Menu* menu) {
	printf("Registering Menu %s\n", name);
	menuRegistry.insert(std::make_pair(name, menu));
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