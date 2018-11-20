#pragma once
#include "SFML/Graphics.hpp"
extern sf::RenderWindow window;
extern bool FullscreenMode;
extern float WindowScaleFactor;

// Opens a window, and closes the current one if already open
// useful for fullscreen toggle and stuff.
void createWindow();