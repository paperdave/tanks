#pragma once
#include "Bullet.h"
#include "Resources.h"
class LargeBullet : public Bullet {
public:
	int EXPLODE_TIME = 0;
	LargeBullet(double x, double y, double dir, float speed) : Bullet(x, y, dir, speed / 3) {
		bounds.width = 20;
		bounds.height = 20;
		beforeTime = 30;
		EXPLODE_TIME = 3 * 60;
	}
	virtual void update() {
		Bullet::update();
		EXPLODE_TIME--;
		if (EXPLODE_TIME < 6 && (EXPLODE_TIME % 2) == 0) {
			playSound("tank/bullet");
			playSound("tank/bullet");
		}
		if (EXPLODE_TIME == 0) {
			screenShake(30, 45);
			//explode
			for (size_t i = 0; i < 360; i += 24) {
				auto bullet = new Bullet(this->x, this->y, i, 5);
				bullet->life = 90 + (rand() % 60);
				
				createObject(bullet);
			}
			destroySelf();
		}
	}
	virtual void render(sf::RenderTarget* g) {
		sf::Sprite s;
		s.setTexture(getTexture("bullet/big"));
		s.setPosition(x, y);
		s.setScale(1, 1);
		s.setOrigin(s.getLocalBounds().width / 2, s.getLocalBounds().height / 2);

		g->draw(s);
	}
};