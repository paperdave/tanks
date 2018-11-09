#include "pch.h"
#include "IntroScene.h"
#include "Resources.h"
#include "GameScene.h"

IntroScene::IntroScene() {

}

void IntroScene::update() {
	if (scale > 0) {
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
	else {
		setScene(new GameScene());
	}
}

void IntroScene::render(sf::RenderTarget* g) {
	sf::View windowView = g->getView();
	g->setView(g->getDefaultView());

	sf::RectangleShape fadetop;
	fadetop.setFillColor(sf::Color(30, 30, 30, bgOpacity));
	fadetop.setPosition(0, 0);
	fadetop.setSize(sf::Vector2f(1280, 720));
	g->draw(fadetop);

	g->setView(windowView);

	sf::Sprite shadow;
	shadow.setTexture(getTexture("title-screen/shadow"));
	shadow.setColor(sf::Color(0, 0, 0, shadowOpacity));
	g->draw(shadow);

	sf::Sprite titleText;
	titleText.setPosition(1280 / 2, 720 / 2),
	titleText.setOrigin(1280 / 2, 720 / 2);
	titleText.setScale(1 + scale, 1 + scale);

	titleText.setTexture(getTexture("title-screen/text-blur"));
	g->draw(titleText, sf::BlendAdd);

	titleText.setTexture(getTexture("title-screen/text"));
	g->draw(titleText);
}