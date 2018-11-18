#include "pch.h"
#include "RapidFirePowerup.h"
#include "Player.h"

RapidFirePowerup::RapidFirePowerup() {}
RapidFirePowerup::~RapidFirePowerup() {}

void RapidFirePowerup::activate() {
	player->rapidFire = true;
}
void RapidFirePowerup::deactivate() {
	player->rapidFire = false;
	player->keyAction = false;

}
void RapidFirePowerup::update() {
	if (player->reload > 7) player->reload = 7;

	timer--;
	if (timer <= 0) {
		active = false;
	}
}

void RapidFirePowerup::render(sf::RenderTarget* g) {

}