#pragma once
#include "SFML/Graphics.hpp"
#include "Maze.h"
#include "GameScene.h"
#include <deque>
 
class GameScene;

enum GameObjectType {
	PlayerType,
	BulletType,
	LightEffectType,
	ParticleType,
	PowerupEntityType
};

class GameObject {
public:
	GameObject();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* g) = 0;

	// Event Handlers
	virtual void event_onKeyPress(sf::Event::KeyEvent event) {};
	virtual void event_onKeyRelease(sf::Event::KeyEvent event) {};

	sf::FloatRect bounds;

	GameScene* scene = nullptr;

protected:
	GameObjectType type;
	Maze getMaze();
	void createObject(GameObject* obj);
	void destroySelf();
	void destroyOther(GameObject* obj);
	std::deque<GameObject*>* getObjectsList();
	GameObject* collisionWith(GameObjectType type);

	void setScene(Scene* newScene);
	void screenShake(float magnitude, int frames);

	bool isDestroyed = false;
};
