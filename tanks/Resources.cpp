#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <deque>
#include <windows.h>

std::map<std::string, sf::Texture> textureRegistry;
std::map<std::string, sf::Font> fontRegistry;
std::map<std::string, sf::SoundBuffer> soundRegistry;
std::deque<sf::Sound> playingSounds;

const std::string getRootFolder() {
	DWORD ftyp = GetFileAttributesA("res/");

	if (ftyp != INVALID_FILE_ATTRIBUTES) {
		return "res/";
	} else {
		return "../res/";
	}
}

void loadTexture(std::string name) {
	sf::Texture loaded;
	std::string path = (getRootFolder() + "texture/" + name + ".png");
	loaded.loadFromFile(path.c_str());
	textureRegistry.insert(std::make_pair(name, loaded));
	LOG("Loading Texture %s from %s\n", name.c_str(), path.c_str());
}
sf::Texture& getTexture(std::string name) {
	std::map<std::string, sf::Texture>::iterator itr = textureRegistry.find(name);
	if (itr == textureRegistry.end()) {
		LOG("Texture not found: %s\n", name.c_str());
		throw "Texture Not Found";
	}
	else {
		return itr->second;
	}
}
void loadFont(std::string name) {
	sf::Font loaded;
	std::string path = (getRootFolder() + "font/" + name + ".ttf");
	loaded.loadFromFile(path.c_str());
	fontRegistry.insert(std::make_pair(name, loaded));
	LOG("Loading Font %s from %s\n", name.c_str(), path.c_str());
}
sf::Font& getFont(std::string name) {
	std::map<std::string, sf::Font>::iterator itr = fontRegistry.find(name);
	if (itr == fontRegistry.end()) {
		LOG("Font not found: %s\n", name.c_str());
		throw "Font Not Found";
	}
	else {
		return itr->second;
	}
}
void loadSound(std::string name) {
	sf::SoundBuffer loaded;
	std::string path = (getRootFolder() + "audio/" + name + ".wav");
	loaded.loadFromFile(path.c_str());
	soundRegistry.insert(std::make_pair(name, loaded));
	LOG("Loading Sound %s from %s\n", name.c_str(), path.c_str());
}
sf::SoundBuffer& getSound(std::string name) {
	std::map<std::string, sf::SoundBuffer>::iterator itr = soundRegistry.find(name);
	if (itr == soundRegistry.end()) {
		LOG("Sound not found: %s\n", name.c_str());
		throw "Sound Not Found";
	}
	else {
		return itr->second;
	}
}

void playSoundRaw(std::string id) {
	sf::Sound snd;
	playingSounds.push_back(snd);
	playingSounds[playingSounds.size() - 1].setBuffer(getSound(id));
	playingSounds[playingSounds.size() - 1].play();
}

void playSound(std::string id) {
	std::map<std::string, sf::SoundBuffer>::iterator itr = soundRegistry.find(id + "1");
	if (itr != soundRegistry.end()) {
		// random sound chooser
		if (rand() % 2 == 0) {
			playSoundRaw(id + "1");
		}
		else {
			playSoundRaw(id + "2");
		}
	} else {
		// just play it
		playSoundRaw(id);
	}
}
void runSoundRecycler() {
	for (size_t i = 0; i < playingSounds.size(); i++) {
		if (playingSounds.at(i).getStatus() == sf::Sound::Stopped) {
			playingSounds.erase(playingSounds.begin() + i);
			i--;
		}
	}
}
