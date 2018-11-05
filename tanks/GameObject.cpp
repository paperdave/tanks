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
	scene->objects.push_back(obj);
}