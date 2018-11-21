#include "pch.h"
#include "TankChooseMenuScene.h"

TankChooseMenuScene::TankChooseMenuScene() {
	playerDummy1.id = 1;
	playerDummy2.id = 2;
	playerDummy3.id = 3;
	playerDummy4.id = 4;

	playerDummy1.x = 0;
	playerDummy2.x = 0;
	playerDummy3.x = 0;
	playerDummy4.x = 0;
	playerDummy1.y = 0;
	playerDummy2.y = 0;
	playerDummy3.y = 0;
	playerDummy4.y = 0;

	playerDummy1.dir = rand() % 360;
	playerDummy2.dir = rand() % 360;
	playerDummy3.dir = rand() % 360;
	playerDummy4.dir = rand() % 360;

	playerDummy1.color = sf::Color(80, 80, 80);
	playerDummy2.color = sf::Color(80, 80, 80);
	playerDummy3.color = sf::Color(80, 80, 80);
	playerDummy4.color = sf::Color(80, 80, 80);
}

TankChooseMenuScene::~TankChooseMenuScene() {

}

void TankChooseMenuScene::update() {
	playerDummy1.dir += 0.2;
	playerDummy2.dir += 0.2;
	playerDummy3.dir -= 0.2;
	playerDummy4.dir += 0.2;

}

void TankChooseMenuScene::render(sf::RenderTarget* g) {
	sf::View view = g->getView();

	view.move(
		((g->getSize().x / -3.25f)),
		((g->getSize().y / -2.0f)));
	view.zoom(0.5);

	g->setView(view);

	playerDummy1.render(g);
	
	view.setSize(g->getSize().x, g->getSize().y);
	view.move(
		((g->getSize().x / -8.0f)),
		0);
	view.zoom(0.5);

	g->setView(view);

	playerDummy2.render(g);

	view.setSize(g->getSize().x, g->getSize().y);
	view.move(
		((g->getSize().x / -8.0f)),
		0);
	view.zoom(0.5);

	g->setView(view);

	playerDummy3.render(g);
	
	view.setSize(g->getSize().x, g->getSize().y);
	view.move(
		((g->getSize().x / -8.0f)),
		0);
	view.zoom(0.5);

	g->setView(view);
	
	playerDummy4.render(g);
}

void TankChooseMenuScene::event_onKeyPress(sf::Event::KeyEvent ev) {

}
void TankChooseMenuScene::event_onKeyRelease(sf::Event::KeyEvent ev) {

}