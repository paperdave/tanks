#include "pch.h"
#include "PlayerControls.h"

PlayerControls makePlayerControls(int left, int right, int up, int down, int action) {
	PlayerControls c;
	c.left = left;
	c.right = right;
	c.up = up;
	c.down = down;
	c.action = action;
	return c;
}
PlayerControlsVisual makePlayerControlsVisuals(const char* left, const char* right, const char* up, const char* down, const char* action) {
	PlayerControlsVisual c;
	c.left = left;
	c.right = right;
	c.up = up;
	c.down = down;
	c.action = action;
	return c;
}

//                                                   A D W  S  SPACE
PlayerControls playerControls1 = makePlayerControls(0, 3, 22, 18, 57);
PlayerControlsVisual playerVisual1 = makePlayerControlsVisuals("A", "D", "W", "S", "Space");
//                                                   < > ^  V  RCTRL
PlayerControls playerControls2 = makePlayerControls(71, 72, 73, 74, 41);
PlayerControlsVisual playerVisual2 = makePlayerControlsVisuals("<", ">", "^", "v", "Right CTRL");
//                                                   J  L  I  K  H
PlayerControls playerControls3 = makePlayerControls(9, 11, 8, 10, 7);
PlayerControlsVisual playerVisual3 = makePlayerControlsVisuals("J", "L", "I", "K", "H");
//                                                   4  6  8  5  0
PlayerControls playerControls4 = makePlayerControls(79, 81, 83, 80, 75);
PlayerControlsVisual playerVisual4 = makePlayerControlsVisuals("4", "6", "8", "5", "0");

PlayerControls getPlayerControlsByID(const int id) {
	switch (id) {
	case 1: return playerControls1;
	case 2: return playerControls2;
	case 3: return playerControls3;
	case 4: return playerControls4;
	}
}
PlayerControlsVisual getPlayerControlsVisualByID(const int id) {
	switch (id) {
	case 1: return playerVisual1;
	case 2: return playerVisual2;
	case 3: return playerVisual3;
	case 4: return playerVisual4;
	}
}

sf::Color player1Color(255, 255, 0);
sf::Color player2Color(255, 0, 255);
sf::Color player3Color(0, 255, 255);
sf::Color player4Color(0, 255, 0);
