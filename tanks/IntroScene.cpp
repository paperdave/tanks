#include "pch.h"
#include "IntroScene.h"
#include "Resources.h"
#include "MenuScene.h"

IntroScene::IntroScene() {
	escapeAction = "exit";

}

void IntroScene::update() {
	if (initDelay > 0) {
		initDelay--;
	}
	else if (scale > 0) {
		scale *= 0.55;
		if (scale < 0.05) {
			scale = 0;
			shadowOpacity = 255;
			screenShake(20, 20);
		}
	}
	else if (shadowOpacity > 100) {
		shadowOpacity -= 4;
		if (shadowOpacity < 100) shadowOpacity = 99;
	}
	else if (delay > 0) {
		delay--;
	}
	else if (bgOpacity > 0) {
		bgOpacity -= 3;
		if (bgOpacity < 0) bgOpacity = 0;
	}
}

void IntroScene::event_onKeyPress(sf::Event::KeyEvent ev) {
	if (ev.code == sf::Keyboard::Space || ev.code == sf::Keyboard::Enter) {
		setScene(startingMenuScene());
		playSound("menu/deactivate");
	}
}

void IntroScene::render(sf::RenderTarget* g) {
	sf::View windowView = g->getView();
	g->setView(g->getDefaultView());

	sf::RectangleShape fadetop;
	fadetop.setFillColor(sf::Color(30, 30, 30, bgOpacity));
	fadetop.setPosition(0, 0);
	fadetop.setSize(sf::Vector2f(g->getSize().x, g->getSize().x));
	g->draw(fadetop);

	g->setView(windowView);

	sf::Text splashtext;
	splashtext.setFont(getFont("clean"));
	splashtext.setString("Press Space to Start");
	splashtext.setPosition(g->getSize().x / 2, g->getSize().y - 64);
	splashtext.setCharacterSize(48);
	splashtext.setOrigin(splashtext.getLocalBounds().width / 2, splashtext.getLocalBounds().height);
	splashtext.setFillColor(sf::Color(30, 30, 30));

	g->draw(splashtext);

	if (initDelay > 0) return;

	sf::Sprite shadow;
	shadow.setPosition(g->getSize().x / 2, g->getSize().y / 2),
	shadow.setOrigin(1280 / 2, 720 / 2);
	shadow.setTexture(getTexture("title-screen/shadow"));
	shadow.setColor(sf::Color(0, 0, 0, shadowOpacity));
	g->draw(shadow);

	sf::Sprite titleText;
	titleText.setPosition(g->getSize().x / 2, g->getSize().y / 2),
	titleText.setOrigin(1280 / 2, 720 / 2);
	titleText.setScale(1 + scale, 1 + scale);

	titleText.setTexture(getTexture("title-screen/text-blur"));
	g->draw(titleText, sf::BlendAdd);

	titleText.setTexture(getTexture("title-screen/text"));
	g->draw(titleText);

}