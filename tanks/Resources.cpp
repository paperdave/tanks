#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <deque>

std::map<std::string, sf::Texture> textureRegistry;
std::map<std::string, sf::Font> fontRegistry;
std::map<std::string, sf::SoundBuffer> soundRegistry;
std::deque<sf::Sound> playingSounds;

sf::Texture& loadTexture(std::string path, std::string name) {
	sf::Texture loaded;
	path = ("../res/texture/" + path);
	loaded.loadFromFile(path.c_str());
	textureRegistry.insert(std::make_pair(name, loaded));
	printf("Loading Texture %s from %s\n", name.c_str(), path.c_str());
	return loaded;
}
sf::Texture& getTexture(std::string name) {
	std::map<std::string, sf::Texture>::iterator itr = textureRegistry.find(name);
	if (itr == textureRegistry.end()) {
		throw "Texture Not Found";
	}
	else {
		return itr->second;
	}
}
sf::Font& loadFont(std::string path, std::string name) {
	sf::Font loaded;
	path = ("../res/font/" + path);
	loaded.loadFromFile(path.c_str());
	fontRegistry.insert(std::make_pair(name, loaded));
	printf("Loading Font %s from %s\n", name.c_str(), path.c_str());
	return loaded;
}
sf::Font& getFont(std::string name) {
	std::map<std::string, sf::Font>::iterator itr = fontRegistry.find(name);
	if (itr == fontRegistry.end()) {
		throw "Font Not Exist";
	}
	else {
		return itr->second;
	}
}
sf::SoundBuffer& loadSound(std::string path, std::string name) {
	sf::SoundBuffer loaded;
	path = ("../res/audio/" + path);
	loaded.loadFromFile(path.c_str());
	soundRegistry.insert(std::make_pair(name, loaded));
	printf("Loading Sound %s from %s\n", name.c_str(), path.c_str());
	return loaded;
}
sf::SoundBuffer& getSound(std::string name) {
	std::map<std::string, sf::SoundBuffer>::iterator itr = soundRegistry.find(name);
	if (itr == soundRegistry.end()) {
		throw "Sound Not Exist";
	}
	else {
		return itr->second;
	}
}

void playSound(std::string id) {
	sf::Sound snd;
	playingSounds.push_back(snd);
	playingSounds[playingSounds.size() - 1].setBuffer(getSound(id));
	playingSounds[playingSounds.size() - 1].play();
}
void runSoundRecycler() {
	for (size_t i = 0; i < playingSounds.size(); i++) {
		if (playingSounds.at(i).getStatus() == sf::Sound::Stopped) {
			playingSounds.erase(playingSounds.begin() + i);
			i--;
		}
	}
}
