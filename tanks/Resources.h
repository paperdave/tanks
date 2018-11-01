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

void loadTexture(std::string name);
sf::Texture& getTexture(std::string name);
void loadFont(std::string name);
sf::Font& getFont(std::string name);
void loadSound(std::string name);
sf::SoundBuffer& getSound(std::string name);

void playSound(std::string id);
void runSoundRecycler();

const std::string getRootFolder();
