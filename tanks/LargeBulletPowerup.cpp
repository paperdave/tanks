#include "pch.h"
#include "LargeBulletPowerup.h"
#include "Player.h"

LargeBulletPowerup::LargeBulletPowerup() {}
LargeBulletPowerup::~LargeBulletPowerup() {}

void LargeBulletPowerup::activate() {
	player->usingLargeBullets = true;
}
void LargeBulletPowerup::deactivate() {
	player->usingLargeBullets = false;
}
void LargeBulletPowerup::update() {
	if (player->keyAction) {
		active = false;
	}
}
void LargeBulletPowerup::render(sf::RenderTarget* g) {
}