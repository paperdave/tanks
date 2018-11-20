// DaveTanks.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h" // required
#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Scene.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "LoadingScene.h"
#include "Resources.h"
#include "BackgroundScene.h"
#include "Utility.h"
#include "Trial.h"
#include "Platform.h"
#include "PreviewExpiredScene.h"
#include "Window.h"
#include <fstream>

sf::View view;
std::unique_ptr<BackgroundScene> bgs;
int soundRecycleTimeout = 30;

bool configAudio = true;
bool configFPS = false;

void update() {
	if (resourcesLoaded) {
		// We have to create the backgroundscene after
		// all resources are loaded, or else we cant
		// get texture information about the bg.

		if (!bgs) bgs = std::unique_ptr<BackgroundScene>(new BackgroundScene());
		// Move BG
		bgs->update();
	}

	// Update current scene
	currentScene->update();

	if (soundRecycleTimeout-- <= 0) {
		soundRecycleTimeout = 30;
		runSoundRecycler();
	}
}
void render() {
	window.clear();

	if (resourcesLoaded) {
		// Apply a default view
		view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
		window.setView(view);

		// Render the background
		bgs->render(&window);
	}

	// Apply shake
	float shakeX = fmod((float)rand(), (shakeRemain * 2.0) + 0.0000000001) - shakeRemain;
	float shakeY = fmod((float)rand(), (shakeRemain * 2.0) + 0.0000000001) - shakeRemain;
	shakeRemain = std::max(0.0f, shakeRemain - ((1 / shakeLength) * shakeMagnitude));

	view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	view.setCenter(window.getSize().x / 2 + shakeX, window.getSize().y / 2 + shakeY);
	window.setView(view);

	// Draw the current scene
	currentScene->render(&window);

	// Display
	window.display();
}

int main(int argc, char* argv[]) {
	#if PRINTF_ENABLE
		createDevConsole();
	#endif

	if (!util_file_exists("config")) {
		// fullscreen, fps, sound
		std::ofstream out("config");
		out << "101";
		out.close();
	}
	else {
		std::ifstream fin("config");
		std::string config_data;
		std::getline(fin, config_data);

		FullscreenMode = config_data.at(0) == '1';
		configFPS = config_data.at(1) == '1';
		configAudio = config_data.at(2) == '1';


		fin.close();
	}

	createWindow();
	
	srand((unsigned int)time(NULL));

	// Set initial scene
#if VERIFY_ENABLED
	if (verify()) {
		currentScene = new LoadingScene();
	} else {
		currentScene = new PreviewExpiredScene();
	}
#else
	currentScene = new LoadingScene();
#endif

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time target_fps = sf::seconds(1.f / 60.f);

	sf::Clock fps_clock;
	sf::Time fps_time = sf::Time::Zero;
	sf::Time second = sf::seconds(1.f);
	int fps = 0;
	int ups = 0;

	sf::Event ev;

	view = window.getView();
	
	while (window.isOpen()) {
		// Poll Events
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) window.close();
			if (ev.type == sf::Event::KeyPressed) {
				if (ev.key.code == sf::Keyboard::F1) {
#if PRINTF_ENABLE
					printf("Restarting %s\n", std::string(typeid(*currentScene).name()).substr(6).c_str());
#endif
					if (typeid(*currentScene).raw_name() == typeid(GameScene).raw_name()) {
						setScene(((GameScene*)currentScene)->cloneStartState());
					} else if (typeid(*currentScene).raw_name() == typeid(MenuScene).raw_name()) {
						setScene(new MenuScene());
					}
				}
				else if (ev.key.code == sf::Keyboard::Escape) {
					executeAction(currentScene->escapeAction, nullptr);
				}
				else if (ev.key.code == sf::Keyboard::F11) {
					FullscreenMode = !FullscreenMode;
					createWindow();
				}
				currentScene->event_onKeyPress(ev.key);
			}
			if (ev.type == sf::Event::KeyReleased) {
				currentScene->event_onKeyRelease(ev.key);
			}
		}

		if (accumulator > target_fps) {
			while (accumulator > target_fps) {
				accumulator -= target_fps;
				update();
				ups++;
			}
			render();
			fps++;
		}
		fps_time += fps_clock.restart();
		accumulator += clock.restart();
		if (fps_time > second) {
			fps_time = sf::Time::Zero;
			printf("FPS: %d, UPS: %d\n", fps, ups);
			fps = 0;
			ups = 0;
		}

		// nextScene is set via setScene(), and is set so that the current
		// scene finishes it's frame before setting a new scene.
		if (nextScene) {
			delete currentScene;
			currentScene = nextScene;
			nextScene = nullptr;
		}
	}

	destroyDevConsole();
	return 0;
}

#ifdef _WIN32

#include <windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	return main(__argc, __argv);
}

#endif