#include "PreviewExpiredScene.h"
#include "Resources.h"
#include "Trial.h"
#include "Platform.h"
#include <chrono>

bool expiredResourceLoaderThreadCompleted = false;
void expiredResourceLoaderThread() {
	// Load up all resources
	loadTexture("tank0/layer0");
	loadTexture("tank0/layer1");
	loadTexture("tank0/layer2");
	loadTexture("tank0/layer3");
	loadTexture("tank0/layer4");
	loadTexture("tank0/layer5");
	loadTexture("tank0/layer6");

	expiredResourceLoaderThreadCompleted = true;
}


PreviewExpiredScene::PreviewExpiredScene() {
	escapeAction = "exit";
	loadFont("clean");
	spawnThread(expiredResourceLoaderThread);
	playerDummy = new Player(sf::Vector2i(0,0), 2);
}

void PreviewExpiredScene::update() {
	playerDummy->dir++;
}

void PreviewExpiredScene::render(sf::RenderTarget* g) {
	sf::RectangleShape rs;
	rs.setFillColor(sf::Color(20, 20, 20));
	rs.setPosition(0, 0);
	rs.setSize(sf::Vector2f(1280, 720));
	g->draw(rs);

	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	sf::Text splashtext;
	splashtext.setFont(getFont("clean"));
	splashtext.setString(VERIFY_TITLE);
	splashtext.setPosition(g->getSize().x / 2, g->getSize().y / 2 - 200 + sin(((double)(ms / 3)) / 100.0) * 3);
	splashtext.setCharacterSize(48);
	splashtext.setOrigin(splashtext.getLocalBounds().width / 2, splashtext.getLocalBounds().height);
	splashtext.setFillColor(sf::Color::White);
	g->draw(splashtext);

	sf::Text desc;
	desc.setFont(getFont("clean"));
	desc.setString(VERIFY_DESC);
	desc.setPosition(g->getSize().x / 2, g->getSize().y / 2);
	desc.setCharacterSize(40);
	desc.setOrigin(desc.getLocalBounds().width / 2, desc.getLocalBounds().height);
	desc.setFillColor(sf::Color(200, 200, 200));
	g->draw(desc);

	sf::Text patreon;
	patreon.setFont(getFont("clean"));
	patreon.setString("https://patreon.com/imdaveead/");
	patreon.setPosition(g->getSize().x / 2, g->getSize().y / 2 + 100);
	patreon.setCharacterSize(32);
	patreon.setOrigin(patreon.getLocalBounds().width / 2, patreon.getLocalBounds().height);
	patreon.setFillColor(sf::Color(249, 104, 84));
	g->draw(patreon);

	if (expiredResourceLoaderThreadCompleted) {
		sf::View playerView = g->getView();
		playerView.zoom(0.5);
		playerView.move(-640, -360);
		g->setView(playerView);

		playerDummy->x = 0;
		playerDummy->y = 130;
		playerDummy->render(g);
	}
}