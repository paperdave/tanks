#include "Transition.h"

Transition::Transition(Scene* scene) {
	this->scene = scene;
}

void Transition::render(sf::RenderTarget* g) {
	sf::RectangleShape cover;
	cover.setFillColor(sf::Color(30, 30, 30));
	cover.setPosition(0, 0);
	cover.setSize(sf::Vector2f(1280, y));

	sf::View viewZoomed = g->getView();
	viewZoomed.zoom(1 - zoom);
	g->setView(viewZoomed);
	scene->render(g);
	
	sf::View view = g->getDefaultView();
	g->setView(view);
	g->draw(cover);
}

void Transition::update() {
	y *= 0.90;
	zoom *= 0.95;

	scene->update();

	if (zoom < 0.001) {
		setScene(scene);
	}
}

void Transition::event_onKeyPress(sf::Event::KeyEvent event) {
	scene->event_onKeyPress(event);
}
void Transition::event_onKeyRelease(sf::Event::KeyEvent event) {
	scene->event_onKeyRelease(event);
}