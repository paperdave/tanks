#include "Transition.h"
#include "Window.h"

Transition::Transition(Scene* scene) {
	this->scene = scene;
	this->escapeAction = scene->escapeAction;
}

void Transition::render(sf::RenderTarget* g) {
	sf::RectangleShape cover;
	cover.setFillColor(sf::Color(30, 30, 30));
	cover.setPosition(0, 0);
	cover.setSize(sf::Vector2f(g->getSize().x, ((float)(y)/1000) * g->getSize().y));

	sf::View viewZoomed = g->getView();
	viewZoomed.zoom((float)(1.0 - zoom));
	g->setView(viewZoomed);
	scene->render(g);
	
	// !!! this breaks for no reason
	try {
		sf::View view = g->getDefaultView();
		g->setView(view);
		g->draw(cover);
	}
	catch (int e) {
		printf("Error on Transition:" + __LINE__);
	}
}

void Transition::update() {
	y *= 0.90;
	zoom *= 0.95;

	scene->update();
	
	// !!! this breaks for no reason
	try {
		if (zoom < 0.001) {
			setScene(scene);
		}
	}
	catch (int e) {
		printf("Error on Transition:" + __LINE__);
	}
}

void Transition::event_onKeyPress(sf::Event::KeyEvent event) {
	scene->event_onKeyPress(event);
}
void Transition::event_onKeyRelease(sf::Event::KeyEvent event) {
	scene->event_onKeyRelease(event);
}