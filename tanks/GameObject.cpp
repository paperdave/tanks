#include "pch.h"
#include "GameObject.h"

GameObject::GameObject() {
	
}

Maze GameObject::getMaze() {
	return scene->maze;
}

void GameObject::destroySelf() {
	auto objects = getObjectsList();
	for (size_t i = 0; i < objects->size(); i++) {
		if (objects->at(i) == this) {
			objects->at(i)->isDestroyed = true;
		}
	}
}
void GameObject::destroyOther(GameObject* obj) {
	auto objects = getObjectsList();
	for (size_t i = 0; i < objects->size(); i++) {
		if (objects->at(i) == obj) {
			objects->at(i)->isDestroyed = true;
			return;
		}
	}
}
void GameObject::createObject(GameObject* obj) {
	obj->scene = scene;
	scene->objects.push_front(obj);
}
std::deque<GameObject*>* GameObject::getObjectsList() {
	return &scene->objects;
}
GameObject* GameObject::collisionWith(GameObjectType type) {
	auto objects = getObjectsList();
	for (size_t i = 0; i < objects->size(); i++) {
		if (objects->at(i)->type == type) {
			if (objects->at(i)->bounds.intersects(bounds)) {
				return objects->at(i);
			}
		}
	}
	return nullptr;
}
void GameObject::setScene(Scene* newScene) {
	nextScene = newScene;
}
void GameObject::screenShake(float magnitude, int frames) {
	shakeMagnitude = std::max(shakeRemain, magnitude);
	shakeRemain += magnitude;
	shakeLength = frames;
}