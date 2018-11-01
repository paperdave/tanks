#pragma once
#include "GameObject.h"
#include "PlayerControls.h"
#include "SFML/Graphics.hpp"

class Player
	: public GameObject {
private:
	double x = 30;
	double y = 30;
	double dir = 90;
	float speed = 2;
	int id = -1;
	float turnSpeed = 2.5;
	float gunOffset = 0.0f;
	bool dead = false;
	int hue;
	sf::FloatRect bounds;
	PlayerControls controls;
	double delay = 100;
	double delayTotal = 18;

	int powerupType = -1;
	int powerupLength = -1;

	bool keyFoward = false;
	bool keyBackwards = false;
	bool keyLeft = false;
	bool keyRight = false;
	bool keyAction = false;
	int sat = 255;

	void HandleKeypress(int code, bool state);
public:
	Player(sf::Vector2i position, int id);

	// Bind key events easily
	void event_onKeyPress(sf::Event::KeyEvent ev) {
		HandleKeypress(ev.code, true);
	}
	void event_onKeyRelease(sf::Event::KeyEvent ev) {
		HandleKeypress(ev.code, false);
	}

	virtual void update();
	virtual void render(sf::RenderTarget* g);
};

