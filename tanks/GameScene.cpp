#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Transition.h"
#include "Utility.h"
#include "MazeGeneration.h"
#include "Resources.h"
#include "IntroScene.h"
#include "PowerupEntity.h"
#include "SFML/Graphics.hpp"
#include "Window.h"
GameScene::GameScene(bool usePlayer1, bool usePlayer2, bool usePlayer3, bool usePlayer4) {
	wallSurface.create(600, 600);
	wallSideSurface.create(600, 600);
	maze = generateMaze(false);

	player1 = usePlayer1;
	player2 = usePlayer2;
	player3 = usePlayer3;
	player4 = usePlayer4;

	sf::Vector2i playerSpots[4];
	for (size_t i = 0; i < 4; i++) {
		bool valid = false;
		while (!valid) {
			int x = rand() % 10;
			int y = rand() % 10;
			valid = true;
			for (size_t j = 0; j < i; j++)
			{
				float dist =
					(playerSpots[j].x - x)*
					(playerSpots[j].x - x)
					+
					(playerSpots[j].y - y)*
					(playerSpots[j].y - y)
					;
				if (dist < 14) {
					valid = false;
					break;
				}
			}
			playerSpots[i].x = x;
			playerSpots[i].y = y;
		}
	}

	for (int i = 1; i <= 4; i++) {

		if (i == 1 && !usePlayer1) continue;
		if (i == 2 && !usePlayer2) continue;
		if (i == 3 && !usePlayer3) continue;
		if (i == 4 && !usePlayer4) continue;

		Player* player = new Player(playerSpots[i - 1], i);
		player->scene = this;
		objects.push_back(player);
	}
}

GameScene::~GameScene() {
	for (size_t i = 0; i < objects.size(); i++) {
		delete objects.at(i);
	}
}

void GameScene::update() {
	int playersAlive = 0;

	switch (state) {
	case RoundState::RoundStateInProgress:
		powerupSpawnCooldown--;
		if (powerupSpawnCooldown <= 0) {
			powerupSpawnCooldown = 450 + rand() % 400;

			PowerupEntity* pe = new PowerupEntity(rand() % 10, rand() % 10, (PowerupType)(rand() % 3));
			pe->scene = this;
			objects.push_back(pe);
		}
		for (std::size_t i = 0; i != objects.size(); ++i) {
			auto obj = objects[i];

			if (obj->isDestroyed) {
				objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
				delete obj;
				i--;
				continue;
			}
			obj->update();
			if (typeid(*obj).name() == typeid(Player).name()) {
				playersAlive++;
				Player* plr = (Player*)obj;
				winner = plr->id;
			}
		}
		if (playersAlive == 1) {
			roundEndTimeout--;
			if (roundEndTimeout <= 0) {
				state = RoundState::RoundStateEnded;
				roundEndTimeout = 120;
			}
		}
		if (playersAlive == 0) {
			state = RoundState::RoundStateEnded;
			winner = -1;
			roundEndTimeout = 120;
		}
		
		break;
	case RoundState::RoundStateEnded:
		topBarsOffset *= 0.95;
		endingZoom *= 0.95;
		textOffset *= 0.945;

		if (roundEndTimeout <= 0) {
			topBarsOffset2 *= 0.85;
		}
		else {
			roundEndTimeout--;
		}

		if (topBarsOffset2 < 12) {
			setScene(new Transition(cloneStartState()));
		}



		break;
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
	view.move(
		((g->getSize().x / -2.0f) +300.0f),
		((g->getSize().y / -2.0f) +300.0f));
	
	Player* player = nullptr;
	for (auto obj : objects) {
		if (typeid(*obj).name() == typeid(Player).name()) {
			player = (Player*)obj;
		}
	}
		
	if(player) {
		int playerX = player->x;
		int playerY = player->y;

		view.move(lerp(-300 + playerX, 0, powf(endingZoom * 0.5, 2)), lerp(-300 + playerY, 0, powf(endingZoom * 0.5, 2)));
		view.zoom(1 / (3 - endingZoom));
	} else {
		view.zoom(1 / ((4 - endingZoom) / 2));
	}
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

	for (auto obj : objects) {
		obj->render(g);
	}

	walls.setColor(sf::Color(255, 255, 255, 255));
	walls.setTexture(wallSurface.getTexture());
	g->draw(walls);

	if (state == RoundStateEnded) {

		sf::View view = g->getDefaultView();
		g->setView(view);
		

		sf::RectangleShape topbar;
		topbar.setPosition(0, 0);
		topbar.setSize(sf::Vector2f(g->getSize().x, (130 - topBarsOffset + 230 - topBarsOffset2)*WindowScaleFactor));
		topbar.setFillColor(sf::Color::Black);
		g->draw(topbar);

		topbar.setPosition(0, g->getSize().y - (130 - topBarsOffset + 230 - topBarsOffset2) * WindowScaleFactor);
		g->draw(topbar);

		sf::Text roundEndText;
		roundEndText.setFont(getFont("clean"));
		roundEndText.setPosition((g->getSize().x/2) - textOffset, ((130 - topBarsOffset + 230 - topBarsOffset2)*WindowScaleFactor)/2);
		roundEndText.setCharacterSize(48);
		if (winner >= 1) {
			roundEndText.setString(getPlayerNameByID(winner) + " Wins!");
			roundEndText.setFillColor(getPlayerColorByID(winner));
		}
		else {
			roundEndText.setFillColor(sf::Color::White);
			roundEndText.setString("It's a Draw!");
		}

		roundEndText.setOrigin(roundEndText.getLocalBounds().width / 2, roundEndText.getLocalBounds().height);
		g->draw(roundEndText);

		topbar.setFillColor(sf::Color(30, 30, 30, (int)lerp(255, 0, topBarsOffset2 / 230.0)));

		topbar.setPosition(0, 0);
		g->draw(topbar);

		topbar.setPosition(0, g->getSize().y - (130 - topBarsOffset + 230 - topBarsOffset2) * WindowScaleFactor);
		g->draw(topbar);
	}
}

GameScene* GameScene::cloneStartState() {
	return new GameScene(player1, player2, player3, player4);
}