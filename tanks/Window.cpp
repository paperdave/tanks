#include "pch.h"
#include "Window.h"
sf::RenderWindow window;

bool currentWindowFullscreenMode = false;
bool FullscreenMode = false;

void createWindow() {
	printf("createWindow();\n");

	if (window.isOpen()) {
		if (currentWindowFullscreenMode == FullscreenMode) return;
		window.close();
	}

	currentWindowFullscreenMode = FullscreenMode;

	if (FullscreenMode) {
		sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
		window.create(desktop, "Dave's Tanks", sf::Style::None);
	}
	else {
		window.create(sf::VideoMode(1280, 720), "Dave's Tanks");
	}
	window.setKeyRepeatEnabled(false);

}