#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <deque>

extern std::map<std::string, sf::Texture> textureRegistry;
extern std::map<std::string, sf::Font> fontRegistry;
extern std::map<std::string, sf::SoundBuffer> soundRegistry;
extern std::deque<sf::Sound> playingSounds;

sf::Texture& loadTexture(std::string name);
sf::Texture& getTexture(std::string name);
sf::Font& loadFont(std::string name);
sf::Font& getFont(std::string name);
sf::SoundBuffer& loadSound(std::string name);
sf::SoundBuffer& getSound(std::string name);

void playSound(std::string id);
void runSoundRecycler();
