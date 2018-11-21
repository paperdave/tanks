#pragma once
#include "SFML/Graphics.hpp"
#include "Config.h"

extern sf::RenderWindow window;
extern float WindowScaleFactor;

// Opens a window, and closes the current one if already open
// useful for fullscreen toggle and stuff.
void createWindow();