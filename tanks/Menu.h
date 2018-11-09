#pragma once
#include <deque>
#include <string>
#include <map>

enum MenuItemType {
	MenuItemTypeLabel,
	MenuItemTypeButton,
	MenuItemTypeDivider
};

struct MenuItem {
	MenuItem(const char* label, MenuItemType type, const char* target) {
		this->label = label;
		this->type = type;
		this->target = target;
	}
	MenuItem(const char* label, MenuItemType type) {
		this->label = label;
		this->type = type;
	}
	MenuItem(MenuItemType type) {
		this->type = type;
	}
	const char* label;
	MenuItemType type;
	const char* target;
};

class Menu {
public:
	Menu(const char* title) {
		this->title = title;
	}
	const char* title;
	std::deque<MenuItem> items;
};

Menu* getMenu(std::string name);
void registerMenu(std::string name, Menu* menu);