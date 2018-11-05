#include "pch.h"
#include "GameScene.h"
#include "MazeGeneration.h"
#include "Player.h"
#include "Resources.h"
#include "SFML/Graphics.hpp"

GameScene::GameScene() {
	wallSurface.create(600, 600);
	wallSideSurface.create(600, 600);
	maze = generateMaze(false);

	for (int i = 1; i <= 4; i++) {
		Player* player = new Player(sf::Vector2i(2, 2 + i), i);
		player->scene = this;
		objects.push_back(player);
	}
}

void GameScene::update() {
	for (auto obj : objects) {
		obj->update();
	}
}

void GameScene::event_onKeyPress(sf::Event::KeyEvent event) {
	for (auto obj : objects) {
		obj->event_onKeyPress(event);
	}
}
void GameScene::event_onKeyRelease(sf::Event::KeyEvent event) {
	for (auto obj : objects) {
		obj->event_onKeyRelease(event);
	}
}

void GameScene::render(sf::RenderTarget* g) {
	// move the view so the 600x600 area is the center
	sf::View view = g->getView();
	view.move(-340, -60);
	g->setView(view);

	wallSurface.clear(sf::Color::Transparent);
	wallSideSurface.clear(sf::Color::Transparent);
	
	// Draw Board
	sf::Sprite boardshadow;
	boardshadow.setTexture(getTexture("board/shadow"));
	boardshadow.setPosition(-50, -50);
	g->draw(boardshadow);

	sf::RectangleShape board;
	board.setFillColor(sf::Color(229, 229, 229, 255));
	board.setOutlineColor(sf::Color(0, 0, 0, 255));
	board.setOutlineThickness(4);
	board.setPosition(0, 0);
	board.setSize(sf::Vector2f(600, 600));
	g->draw(board);

	// Draw Maze
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			// Down Line
			if (j < 9 && maze.grid[i][j].down) {
				sf::RectangleShape lineDown;
				lineDown.setOutlineColor(sf::Color(0, 0, 0, 255));
				lineDown.setOutlineThickness(2);
				lineDown.setPosition(i * 60, j * 60 + 60);
				lineDown.setSize(sf::Vector2f(60, 0));
				wallSurface.draw(lineDown);

				sf::Sprite wall;
				wall.setTexture(getTexture("wall/side-h"));
				wall.setPosition(i * 60 - 2, j * 60 + 60 + 2);
				wallSideSurface.draw(wall);

			}
			// Right Line
			if (i < 9 && maze.grid[i][j].right) {
				sf::RectangleShape lineRight;
				lineRight.setOutlineColor(sf::Color(0, 0, 0, 255));
				lineRight.setOutlineThickness(2);
				lineRight.setPosition(i * 60 + 60, j * 60);
				lineRight.setSize(sf::Vector2f(0, 62));
				wallSurface.draw(lineRight);
				
				sf::Sprite wall;
				wall.setTexture(getTexture("wall/side-v"));
				wall.setPosition(i * 60 + 60 - 2, j * 60 + 60 + 2);
				wallSideSurface.draw(wall);

			}
			// non edge
			if (j != 0 && i != 0) {
				if (maze.grid[i - 1][j].right || maze.grid[i][j - 1].down || maze.grid[i - 1][j - 1].down || maze.grid[i - 1][j].right) {
					sf::RectangleShape dot;
					dot.setFillColor(sf::Color(0, 0, 0, 255));
					dot.setPosition(i * 60 - 2, j * 60 - 2);
					dot.setSize(sf::Vector2f(4, 4));
					wallSurface.draw(dot);
				}
			}
		}
	}

	sf::Sprite walls;
	walls.setTexture(wallSideSurface.getTexture());
	walls.setPosition(0, 600);
	walls.setScale(sf::Vector2f(1, -1));
	walls.setColor(sf::Color(255, 255, 255, 120));
	g->draw(walls);

	walls.setColor(sf::Color(255, 255, 255, 255));
	walls.setTexture(wallSurface.getTexture());
	g->draw(walls);

	for (auto obj : objects) {
		obj->render(g);
	}

}