#include "pch.h"
#include "TankChooseMenuScene.h"
#include "Resources.h"

TankChooseMenuScene::TankChooseMenuScene(std::string endActionStr, std::string titleText) {
	playerDummy1.id = 1;
	playerDummy2.id = 2;
	playerDummy3.id = 3;
	playerDummy4.id = 4;

	playerDummy1.x = 0;
	playerDummy2.x = 0;
	playerDummy3.x = 0;
	playerDummy4.x = 0;
	playerDummy1.y = 10;
	playerDummy2.y = 10;
	playerDummy3.y = 10;
	playerDummy4.y = 10;

	playerDummy1.dir = rand() % 360;
	playerDummy2.dir = rand() % 360;
	playerDummy3.dir = rand() % 360;
	playerDummy4.dir = rand() % 360;

	endAction = endActionStr;
	title = titleText;
}

TankChooseMenuScene::~TankChooseMenuScene() {

}

void TankChooseMenuScene::update() {
	playerDummy1.dir += 0.2;
	playerDummy2.dir += 0.2;
	playerDummy3.dir -= 0.2;
	playerDummy4.dir += 0.2;

	int count = 0;
	if (player1) count++;
	if (player2) count++;
	if (player3) count++;
	if (player4) count++;

	if (count > 1) {
		if (timeOut >= 90) {
			setScene(new GameScene(player1, player2, player3, player4, endAction));
		}
		else {
			timeOut++;
		}
	}
	else {
		timeOut = timeOut * 0.6;
	}
}

#define tank_not_chosen_gray sf::Color(80,80,80)

void TankChooseMenuScene::render(sf::RenderTarget* g) {
	if (player1) {
		playerDummy1.color = player1Color;
	}
	else {
		playerDummy1.color = tank_not_chosen_gray;
	}
	if (player2) {
		playerDummy2.color = player2Color;
	}
	else {
		playerDummy2.color = tank_not_chosen_gray;
	}
	if (player3) {
		playerDummy3.color = player3Color;
	}
	else {
		playerDummy3.color = tank_not_chosen_gray;
	}
	if (player4) {
		playerDummy4.color = player4Color;
	}
	else {
		playerDummy4.color = tank_not_chosen_gray;
	}

	sf::View view = g->getView();
	g->setView(g->getDefaultView());

	//BG
	sf::RectangleShape bg;
	bg.setSize(sf::Vector2f(g->getSize().x, g->getSize().y));
	bg.setFillColor(sf::Color(230, 230, 230));
	g->draw(bg, sf::BlendMultiply);

	g->setView(view);

	// DRAW BAR
	sf::RectangleShape bar;
	bar.setPosition(8, g->getSize().y - g->getSize().y / 16.0f - 8);
	bar.setSize(sf::Vector2f(g->getSize().x - 18, g->getSize().y / 16.0f));
	bar.setFillColor(sf::Color(107, 107, 107));
	bar.setOutlineThickness(8);
	bar.setOutlineColor(sf::Color(80, 80, 80));
	g->draw(bar);
	if (timeOut > 0) {
		bar.setSize(sf::Vector2f((g->getSize().x - 18) * (timeOut / 90.0f), g->getSize().y / 16.0f));
		bar.setFillColor(sf::Color(242,75,75));
		bar.setOutlineThickness(8);
		bar.setOutlineColor(sf::Color(178, 53, 53));
		g->draw(bar);
	}

	// DRAW BOTTOM TEXT
	sf::Text splashtext;
	splashtext.setFont(getFont("clean"));
	splashtext.setString(timeOut == 0 ? "Waiting for Players..." : "Game is Starting...");
	splashtext.setPosition(g->getSize().x / 2, g->getSize().y - (g->getSize().y / 32.0f));
	splashtext.setCharacterSize(24);
	splashtext.setOrigin(splashtext.getLocalBounds().width / 2, 1.5*splashtext.getLocalBounds().height);
	splashtext.setFillColor(sf::Color::White);
	g->draw(splashtext);

	// DRAW TOP TEXT
	sf::Text top;
	top.setFont(getFont("clean"));
	top.setString(title);
	top.setPosition(g->getSize().x / 2, 50);
	top.setCharacterSize(48);
	top.setOrigin(top.getLocalBounds().width / 2, 1.5*top.getLocalBounds().height);
	top.setFillColor(sf::Color::Black);
	g->draw(top);

	// DRAW PLAYERS
	view.move(
		((g->getSize().x / -3.25f)),
		((g->getSize().y / -2.0f)));
	view.zoom(0.5);

	g->setView(view);

	sf::Sprite controls;
	controls.setTexture(getTexture("key/wasd"));
	controls.setPosition(sf::Vector2f(0, -90));
	controls.setScale(0.3, 0.3);
	controls.setOrigin(250, 250);

	playerDummy1.render(g);
	g->draw(controls);

	view.zoom(2);
	view.move(
		((g->getSize().x / -8.0f)),
		0);
	view.zoom(0.5);

	g->setView(view);

	playerDummy2.render(g);
	controls.setTexture(getTexture("key/arrows"));
	g->draw(controls);

	view.zoom(2);
	view.move(
		((g->getSize().x / -8.0f)),
		0);
	view.zoom(0.5);

	g->setView(view);

	playerDummy3.render(g);
	controls.setTexture(getTexture("key/who-tf-came-up-with-this-one"));
	g->draw(controls);

	view.zoom(2);
	view.move(
		((g->getSize().x / -8.0f)),
		0);
	view.zoom(0.5);

	g->setView(view);
	
	playerDummy4.render(g);
	controls.setTexture(getTexture("key/numpad"));
	g->draw(controls);
}

void TankChooseMenuScene::event_onKeyPress(sf::Event::KeyEvent ev) {
	if (ev.code == playerControls1.action) player1 = !player1;
	if (ev.code == playerControls2.action) player2 = !player2;
	if (ev.code == playerControls3.action) player3 = !player3;
	if (ev.code == playerControls4.action) player4 = !player4;

	if (ev.code == playerControls1.left) playerDummy1.keyLeft = true;
	if (ev.code == playerControls2.left) playerDummy2.keyLeft = true;
	if (ev.code == playerControls3.left) playerDummy3.keyLeft = true;
	if (ev.code == playerControls4.left) playerDummy4.keyLeft = true;

	if (ev.code == playerControls1.right) playerDummy1.keyRight = true;
	if (ev.code == playerControls2.right) playerDummy2.keyRight = true;
	if (ev.code == playerControls3.right) playerDummy3.keyRight = true;
	if (ev.code == playerControls4.right) playerDummy4.keyRight = true;

}
void TankChooseMenuScene::event_onKeyRelease(sf::Event::KeyEvent ev) {
	if (ev.code == playerControls1.left) playerDummy1.keyLeft = false;
	if (ev.code == playerControls2.left) playerDummy2.keyLeft = false;
	if (ev.code == playerControls3.left) playerDummy3.keyLeft = false;
	if (ev.code == playerControls4.left) playerDummy4.keyLeft = false;

	if (ev.code == playerControls1.right) playerDummy1.keyRight = false;
	if (ev.code == playerControls2.right) playerDummy2.keyRight = false;
	if (ev.code == playerControls3.right) playerDummy3.keyRight = false;
	if (ev.code == playerControls4.right) playerDummy4.keyRight = false;
}