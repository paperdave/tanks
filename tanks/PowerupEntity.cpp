#include "pch.h"
#include "PowerupEntity.h"
#include "Resources.h"

PowerupEntity::PowerupEntity(int gridx, int gridy, PowerupType powerup) {
	x = gridx;
	y = gridy;
	powerupType = powerup;

	bounds.left = gridx * 60 + 22;
	bounds.top = gridy * 60 + 22;
	bounds.height = 16;
	bounds.width = 16;

	type = PowerupEntityType;
}

PowerupEntity::~PowerupEntity() {

}

void PowerupEntity::update() {
	z *= 0.8;
	angle++;
	if (beamwidth < 1) beamwidth = 0;
	else beamwidth *= 0.9;
}

void PowerupEntity::render(sf::RenderTarget* g) {
	sf::RectangleShape beam;
	beam.setSize(sf::Vector2f(beamwidth, 1000 + 60 * y));
	beam.setPosition(60 * x + (60 - beamwidth) * 0.5, -1000 + 30);
	beam.setFillColor(getPowerupColor(this->powerupType));
	g->draw(beam, sf::BlendAdd);

	sf::Sprite spr;
	spr.setTexture(getTexture("power/power" + std::to_string(powerupType) +"/layer0"));
	spr.setPosition(x * 60 + 30, y * 60 - z + 30);
	spr.setRotation(angle);
	spr.setOrigin(30, 30);
	
	g->draw(spr);

	spr.setTexture(getTexture("power/power" + std::to_string(powerupType) + "/layer1"));
	spr.move(0, -1);
	g->draw(spr);

	spr.setTexture(getTexture("power/power" + std::to_string(powerupType) + "/layer2"));
	spr.move(0, -1);
	g->draw(spr);

	spr.setTexture(getTexture("power/power" + std::to_string(powerupType) + "/layer3"));
	spr.move(0, -1);
	g->draw(spr);

	spr.setTexture(getTexture("power/power" + std::to_string(powerupType) + "/layer4"));
	spr.move(0, -1);
	g->draw(spr);
}
