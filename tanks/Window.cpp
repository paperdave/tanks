#include "pch.h"
#include "Window.h"
#include "Config.h"
sf::RenderWindow window;

bool currentWindowFullscreenMode = false;

float WindowScaleFactor = 1;

void createWindow() {
	printf("createWindow();\n");

	if (window.isOpen()) {
		if (currentWindowFullscreenMode == configFullscreen) return;
		window.close();
	}

	currentWindowFullscreenMode = configFullscreen;

	if (configFullscreen) {
		sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
		window.create(desktop, "Dave's Tanks", sf::Style::None);
	}
	else {
		window.create(sf::VideoMode(1280, 720), "Dave's Tanks");
	}
	window.setKeyRepeatEnabled(false);

	WindowScaleFactor = window.getSize().x / 1280.0f;

	sf::sleep(sf::milliseconds(250));
}