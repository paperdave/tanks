#include "pch.h"
#include "GameObject.h"

GameObject::GameObject() {
	
}

Maze GameObject::getMaze() {
	return scene->maze;
}

void GameObject::destroySelf() {
	scene->objects.erase(std::remove(scene->objects.begin(), scene->objects.end(), this), scene->objects.end());
}
void GameObject::createObject(GameObject* obj) {
	obj->scene = scene;
	scene->objects.push_back(obj);
}
std::deque<GameObject*>* GameObject::getObjectsList() {
	return &scene->objects;
}
GameObject* collisionWith(sf::FloatRect bounds, GameObjectType type) {
	return nullptr;
}