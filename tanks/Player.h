#pragma once
#include "GameObject.h"
#include "PlayerControls.h"
#include "Powerup.h"
#include "SFML/Graphics.hpp"

class GameObject;

class Player : public GameObject {
public:
	float speed = 2.0f;
	float turnSpeed = 4.0f;
	float bulletSpeed = 4.9f;
	float gunOffset = 0.0f;
	bool dead = false;
	sf::Color color;
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

	void HandleKeypress(int code, bool state);
	bool collisionSquare(int squareX, int squareY);
	bool collisionAt(double x, double y);
	
	int id;
	int activePowerupID;
	double x = 30;
	double y = 30;
	double dir = 90;

	Player(sf::Vector2i position, int id);
	~Player();
	Player() {
		Player(sf::Vector2i(0, 0), 1);
	}

	// Bind key events easily
	void event_onKeyPress(sf::Event::KeyEvent ev)   { HandleKeypress(ev.code, true);  }
	void event_onKeyRelease(sf::Event::KeyEvent ev) { HandleKeypress(ev.code, false); }

	virtual void update();
	virtual void render(sf::RenderTarget* g);

	Powerup* activePowerup = nullptr;

	void activatePowerup(Powerup *);

	int reload = 30;
	bool rapidFire = false;
	bool usingLargeBullets = false;

};

