#pragma once
#include "pch.h"
#include "LoadingScene.h"

#include "MenuScene.h"
#include "GameScene.h"
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Platform.h"
#include "Utility.h"
#include "Constants.h"
#include "MenuContent.h"
#include <fstream>
#include <deque>
#include <iostream>
#include <thread>
#include <chrono>
#include <filesystem>

bool loadingThreadComplete = false;

namespace {
	void replaceAll(std::string& str, const std::string& from, const std::string& to) {
		if (from.empty())
			return;
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
	}
	bool replace(std::string& str, const std::string& from, const std::string& to) {
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}
}

void resourceThread() {
	// Load up all resources
	std::string root = getRootFolder();

	#pragma warning(disable : 4996) // This is deprecated, not sure what else to use for now.
	for (std::tr2::sys::recursive_directory_iterator i(root), end; i != end; ++i) {
	#pragma warning(default : 4996) 

		if (!is_directory(i->path())) {

			std::string name = i->path().string().substr(root.length());

			replaceAll(name, "\\", "/");

			if (replace(name, "texture/", "")) {
				loadTexture(name.substr(0, name.length() - 4));
			}
			if (replace(name, "audio/", "")) {
				loadSound(name.substr(0, name.length() - 4));
			}
		}
	}

	registerAllMenus();
	
	#if 0
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	#endif

	loadingThreadComplete = true;
	resourcesLoaded = true;

	printf("Loading Completed\n");
}


// Load the proggy font, init the resource loader thread
// and choose a loading line.
LoadingScene::LoadingScene() {
	
	loadFont("clean");

	std::deque<std::string> loadingLines;
	std::ifstream fin(getRootFolder() + "tips.txt");
	std::string line;
	while (std::getline(fin, line)) {
		loadingLines.push_back(line);
	}

	int randomIndex = rand() % loadingLines.size();
	this->loadingLine = loadingLines[randomIndex];
	
	this->fadetop_opacity = 0;

	spawnThread(resourceThread);
	
}

void LoadingScene::update() {
	if (loadingThreadComplete) {
			if (fadetop_opacity < 255) {
				fadetop_opacity += 10;
				if (fadetop_opacity > 255) {
					fadetop_opacity = 255;
				}
			} else {
				// !!! Make a setScene to set it after a frame is completed.
				setScene(new MenuScene());
			}
	}
}

void LoadingScene::render(sf::RenderTarget* g) {
	sf::RectangleShape rs;
	rs.setFillColor(sf::Color(20, 20, 20));
	rs.setPosition(0, 0);
	rs.setSize(sf::Vector2f(1280, 720));

	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	sf::Text splashtext;
	splashtext.setFont(getFont("clean"));
	splashtext.setString("Loading...");
	splashtext.setPosition(g->getSize().x / 2, g->getSize().y / 2 + sin(((double)(ms / 3)) / 100.0) * 15);
	splashtext.setCharacterSize(96);
	splashtext.setOrigin(splashtext.getLocalBounds().width / 2, splashtext.getLocalBounds().height);
	splashtext.setFillColor(sf::Color::White);

	sf::Text loadingline;
	loadingline.setFont(getFont("clean"));
	loadingline.setString(this->loadingLine);
	loadingline.setPosition(32, g->getSize().y - 32);
	loadingline.setCharacterSize(24);
	loadingline.setOrigin(0, 24);
	loadingline.setFillColor(sf::Color::White);

	sf::Text date;
	date.setFont(getFont("clean"));
	date.setString("Built on " + BUILD_DATESTAMP);
	date.setCharacterSize(24);
	date.setOrigin(200, 24);
	date.setPosition(g->getSize().x - 32, g->getSize().y - 32);
	date.setFillColor(sf::Color::White);

	g->draw(rs);
	g->draw(splashtext);
	g->draw(loadingline);
	g->draw(date);

	if (loadingThreadComplete) {
		sf::RectangleShape fadetop;
		fadetop.setFillColor(sf::Color(30, 30, 30, this->fadetop_opacity));
		fadetop.setPosition(0, 0);
		fadetop.setSize(sf::Vector2f(1280, 720));

		g->draw(fadetop);
	}
}