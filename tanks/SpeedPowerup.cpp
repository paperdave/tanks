#include "pch.h"
#include "SpeedPowerup.h"
#include "Player.h"

SpeedPowerup::SpeedPowerup() {}
SpeedPowerup::~SpeedPowerup() {}

void SpeedPowerup::activate() {
	player->speed += 2;
	player->turnSpeed += 3;
}
void SpeedPowerup::deactivate() {
	player->speed -= 2;
	player->turnSpeed -= 3;
}
void SpeedPowerup::update() {
	timer--;
	if (timer <= 0) {
		active = false;
	}
}

void SpeedPowerup::render(sf::RenderTarget* g) {
	
}