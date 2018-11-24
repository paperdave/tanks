#pragma once
#include "Scene.h"
#include "Maze.h"
#include "GameObject.h"
#include <deque>
#include <SFML/Graphics.hpp>

extern int streakP1;
extern int streakP2;
extern int streakP3;
extern int streakP4;

class GameObject;

enum RoundState {
	RoundStateInProgress,
	RoundStateEnded
};

class GameScene : public Scene {
private:
	sf::RenderTexture wallSideSurface;
	sf::RenderTexture wallSurface;
	int roundEndTimeout = 90;
	RoundState state = RoundStateInProgress;
	int winner = -1;
	int powerupSpawnCooldown = 350 + rand() % 100;

	int topBarsOffset = 130;
	int topBarsOffset2 = 230;
	double endingZoom = 2;
	double textOffset = 1000;
	
	bool player1;
	bool player2;
	bool player3;
	bool player4;

	std::string afterAction;
public:
	GameScene(bool usePlayer1, bool usePlayer2, bool usePlayer3, bool usePlayer4, std::string afterAction);
	virtual ~GameScene();

	virtual void render(sf::RenderTarget* g);
	virtual void update();
	virtual void event_onKeyPress(sf::Event::KeyEvent event);
	virtual void event_onKeyRelease(sf::Event::KeyEvent event);
	
	Maze maze;
	std::deque<GameObject*> objects;

	// clones starting state
	GameScene* cloneStartState();
};

