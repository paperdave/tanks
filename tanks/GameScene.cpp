#include "pch.h"
#include "GameScene.h"
#include "MazeGeneration.h"
#include "SFML/Graphics.hpp"


GameScene::GameScene() {
	shadowSurface.create(600, 600);
	maze = generateMaze(false);
}

void GameScene::render(sf::RenderTarget* g) {
	// move the view so the 600x600 area is the center
	sf::View view = g->getView();
	view.move(-340, -60);
	g->setView(view);

	this->shadowSurface.clear(sf::Color::Transparent);
	
	// Draw Board
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(229, 229, 229, 255));
	rect.setOutlineColor(sf::Color(0, 0, 0, 255));
	rect.setOutlineThickness(4);
	rect.setPosition(0, 0);
	rect.setSize(sf::Vector2f(600, 600));
	g->draw(rect);

	// Draw Maze
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 10; j++) {
			// Down Line
			if (maze.grid[i][j].down) {
				sf::RectangleShape lineDown;
				lineDown.setOutlineColor(sf::Color(0, 0, 0, 255));
				lineDown.setOutlineThickness(2);
				lineDown.setPosition(i * 60, j * 60 + 60);
				lineDown.setSize(sf::Vector2f(60, 0));
				this->shadowSurface.draw(lineDown);
			}
			// Right Line
			if (maze.grid[i][j].right) {
				sf::RectangleShape lineRight;
				lineRight.setOutlineColor(sf::Color(0, 0, 0, 255));
				lineRight.setOutlineThickness(2);
				lineRight.setPosition(i * 60 + 60, j * 60);
				lineRight.setSize(sf::Vector2f(0, 60));
				this->shadowSurface.draw(lineRight);
			}
			// non edge
			if (j != 0 && i != 0) {
				if (maze.grid[i - 1][j].right || maze.grid[i][j - 1].down || maze.grid[i - 1][j - 1].down || maze.grid[i - 1][j].right) {
					sf::RectangleShape dot;
					dot.setFillColor(sf::Color(0, 0, 0, 255));
					dot.setPosition(i * 60 - 2, j * 60 - 2);
					dot.setSize(sf::Vector2f(4, 4));
					this->shadowSurface.draw(dot);
				}
			}
		}
	}

	sf::Sprite shadows;
	shadows.setTexture(this->shadowSurface.getTexture());
	shadows.setPosition(0, 600 + 4);
	shadows.setColor(sf::Color(0, 0, 0, 70));
	shadows.setScale(sf::Vector2f(1, -1));
	g->draw(shadows);
	shadows.setColor(sf::Color::White);
	shadows.setPosition(0, 600);
	g->draw(shadows);
}