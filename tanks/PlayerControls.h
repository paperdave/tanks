#pragma once
#include <SFML/Graphics.hpp>

struct PlayerControls {
	int left;
	int right;
	int up;
	int down;
	int action;
};
struct PlayerControlsVisual {
	const char* left;
	const char* right;
	const char* up;
	const char* down;
	const char* action;
};

extern PlayerControls playerControls1;
extern PlayerControlsVisual playerVisual1;
extern PlayerControls playerControls2;
extern PlayerControlsVisual playerVisual2;
extern PlayerControls playerControls3;
extern PlayerControlsVisual playerVisual3;
extern PlayerControls playerControls4;
extern PlayerControlsVisual playerVisual4;

PlayerControls getPlayerControlsByID(const int id);
PlayerControlsVisual getPlayerControlsVisualByID(const int id);

extern sf::Color player1Color;
extern sf::Color player2Color;
extern sf::Color player3Color;
extern sf::Color player4Color;
