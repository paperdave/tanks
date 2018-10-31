#pragma once
#include "pch.h"
#include "LoadingScene.h"

#include "Scene.h"
#include "GameScene.h"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Constants.h"
#include <Windows.h>
#include <fstream>
#include <deque>

bool loadingThreadComplete = false;

DWORD WINAPI resourceLoaderThread(LPVOID lpParameter) {
	// Load up all resources
	loadTexture("tank-0");
	loadTexture("tank-1");
	loadTexture("tank-2");
	loadTexture("tank-3");
	loadTexture("tank-4");
	loadTexture("test-image");
	loadTexture("tank-tip");
	loadTexture("bullet-0");
	loadTexture("bullet-1");
	loadTexture("bullet-2");
	loadTexture("power-0");
	loadTexture("power-1");
	loadTexture("power-2");
	loadTexture("power-3");
	loadTexture("power-4");
	loadSound("menu1");
	loadSound("menu2");
	loadSound("dead1");
	loadSound("dead2");
	loadSound("bullet");
	loadSound("powerup");
	loadSound("round_switch");
	loadSound("round_end");
	loadTexture("background");

	if (false)
		Sleep(1000); // >:)

	loadingThreadComplete = true;
	resourcesLoaded = true;

	return 0;
}

// Load the proggy font, init the resource loader thread
// and choose a loading line.
LoadingScene::LoadingScene() {
	
	loadFont("clean");

	std::deque<std::string> loadingLines;
	std::ifstream fin("../res/tips.txt");
	std::string line;
	while (std::getline(fin, line)) {
		loadingLines.push_back(line);
	}

	int randomIndex = rand() % loadingLines.size();
	this->loadingLine = loadingLines[randomIndex];
	
	this->fadetop_opacity = 0;

	DWORD threadID;
	HANDLE hand = CreateThread(0, 0, resourceLoaderThread, 0, 0, &threadID);
}

void LoadingScene::update() {
	if (loadingThreadComplete) {
			if (this->fadetop_opacity < 255) {
				this->fadetop_opacity++;
			} else {
				currentScene = new GameScene();
			}
	}

	SYSTEMTIME st;
	GetSystemTime(&st);
	time = st.wMilliseconds + st.wSecond * 1000 + st.wMinute * 60000;
}

void LoadingScene::render(sf::RenderTarget* g) {
	sf::RectangleShape rs;
	rs.setFillColor(sf::Color(20,20,20));
	rs.setPosition(0, 0);
	rs.setSize(sf::Vector2f(1280, 720));

	
	sf::Text splashtext;
	splashtext.setFont(getFont("clean"));
	splashtext.setString("Loading...");
	splashtext.setPosition(g->getSize().x / 2, g->getSize().y / 2 + sin(time / 300.0f) * 15);
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

	g->draw(rs);
	g->draw(splashtext);
	g->draw(loadingline);

	if (loadingThreadComplete) {
		sf::RectangleShape fadetop;
		fadetop.setFillColor(sf::Color(30, 30, 30, this->fadetop_opacity));
		fadetop.setPosition(0, 0);
		fadetop.setSize(sf::Vector2f(1280, 720));

		g->draw(fadetop);
	}
}