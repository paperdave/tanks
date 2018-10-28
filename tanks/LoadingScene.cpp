#pragma once
#include "pch.h"
#include "LoadingScene.h"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include <Windows.h>
#include <fstream>
#include <deque>

bool loadingThreadComplete = false;

DWORD WINAPI resourceLoaderThread(LPVOID lpParameter) {
	// Load up all resources
	loadTexture("tank0.png", "player-0");
	loadTexture("tank1.png", "player-1");
	loadTexture("tank2.png", "player-2");
	loadTexture("tank3.png", "player-3");
	loadTexture("tank4.png", "player-4");
	loadTexture("tank_tip.png", "player-gun");
	loadTexture("bullet_0.png", "bullet_0");
	loadTexture("bullet_1.png", "bullet_1");
	loadTexture("bullet_2.png", "bullet_2");
	loadTexture("powerA.png", "power1");
	loadTexture("powerB.png", "power2");
	loadTexture("powerC.png", "power3");
	loadTexture("powerD.png", "power4");
	loadTexture("powerE.png", "power5");
	loadSound("damage.wav", "a-lot-of-damage");
	loadSound("menu1.wav", "menu1");
	loadSound("menu2.wav", "menu2");
	loadSound("dead1.wav", "dead1");
	loadSound("dead2.wav", "dead2");
	loadSound("bullet.wav", "bullet");
	loadSound("powerup.wav", "powerup");
	loadSound("round_switch.wav", "round_switch");
	loadSound("round_end.wav", "round_end");
	loadSound("damage.wav", "a-lot-of-damage");

	Sleep(1000); // >:)

	loadingThreadComplete = true;

	return 0;
}

// Load the proggy font, init the resource loader thread
// and choose a loading line.
LoadingScene::LoadingScene() {
	
	loadFont("ProggyClean.ttf", "proggy");

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

LoadingScene::~LoadingScene() {
	
}

void LoadingScene::render(sf::RenderTarget* g) {
	sf::RectangleShape rs;
	rs.setFillColor(sf::Color(20,20,20));
	rs.setPosition(0, 0);
	rs.setSize(sf::Vector2f(1280, 720));

	SYSTEMTIME st;
	GetSystemTime(&st);
	long int time = st.wMilliseconds + st.wSecond * 1000 + st.wMinute * 60000;

	sf::Text splashtext;
	splashtext.setFont(getFont("proggy"));
	splashtext.setString("Loading...");
	splashtext.setPosition(g->getSize().x / 2, g->getSize().y / 2 + sin(time / 300.0f) * 15);
	splashtext.setCharacterSize(96);
	splashtext.setOrigin(splashtext.getLocalBounds().width / 2, splashtext.getLocalBounds().height);
	splashtext.setFillColor(sf::Color::White);

	sf::Text loadingline;
	loadingline.setFont(getFont("proggy"));
	loadingline.setString(this->loadingLine);
	loadingline.setPosition(32, g->getSize().y - 32);
	loadingline.setCharacterSize(24);
	loadingline.setOrigin(0, 24);
	loadingline.setFillColor(sf::Color::White);

	g->draw(rs);
	g->draw(splashtext);
	g->draw(loadingline);

	if (loadingThreadComplete) {
		if (this->fadetop_opacity < 255) {
			this->fadetop_opacity++;
		}

		sf::RectangleShape fadetop;
		fadetop.setFillColor(sf::Color(10, 10, 10, this->fadetop_opacity));
		fadetop.setPosition(0, 0);
		fadetop.setSize(sf::Vector2f(1280, 720));

		g->draw(fadetop);
	}
}