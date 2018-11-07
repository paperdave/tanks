#pragma once
#include "pch.h"
#include "Scene.h"
#include <algorithm>

float shakeRemain = 1.0;
float shakeMagnitude = 1.0;
float shakeLength = 1.0;

Scene* currentScene = nullptr;
Scene* nextScene = nullptr;

Scene::Scene() {}

void Scene::setScene(Scene* newScene) {
	nextScene = newScene;
}
void Scene::screenShake(float magnitude, int frames) {
	shakeMagnitude = std::max(shakeRemain, magnitude);
	shakeRemain += magnitude;
	shakeLength = frames;
}