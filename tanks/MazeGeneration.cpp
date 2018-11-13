#include "pch.h"
#include "MazeGeneration.h"
#include "Maze.h"
#include <stdio.h>
#include <vector>

struct pos {
	int x;
	int y;
};

Maze generateMaze(bool log = false) {
	// Step 1. Fill a with walls
	Maze m = Maze();
						  // Step 2. Choose a starting coord

	int startx = rand() % 10;
	int starty = rand() % 10;
	pos position1;
	position1.x = startx;
	position1.y = starty;
	bool visitedMap[10][10];
	std::vector<pos> subTrees;
	subTrees.push_back(position1);
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 10; j++) {
			visitedMap[i][j] = false;
		}
	}
	visitedMap[startx][starty] = true;

	while (subTrees.size() > 0) {
		pos p = subTrees.at(0);
		int currentx = p.x;
		int currenty = p.y;
		subTrees.erase(subTrees.begin());
		while (true) {
			std::vector<int> dirs;
			if (currentx != 0) if (!visitedMap[currentx - 1][currenty]) {
				dirs.push_back(0);
			}
			if (currentx != 9) if (!visitedMap[currentx + 1][currenty]) {
				dirs.push_back(1);
			}
			if (currenty != 0) if (!visitedMap[currentx][currenty - 1]) {
				dirs.push_back(2);
			}
			if (currenty != 9) if (!visitedMap[currentx][currenty + 1]) {
				dirs.push_back(3);
			}

			if (dirs.size() == 0) {
				break;
			};

			int rd = rand() % dirs.size();
			switch (dirs[rd]) {
			case 2: // UP
				m.setWallUp(currentx, currenty, false);
				currenty--;
				break;
			case 3: // DOWN
				m.setWallDown(currentx, currenty, false);
				currenty++;
				break;
			case 0: // LEFT
				m.setWallLeft(currentx, currenty, false);
				currentx--;
				break;
			case 1: // RIGHT
				m.setWallRight(currentx, currenty, false);
				currentx++;
				break;
			}
			pos newpos;
			newpos.x = currentx;
			newpos.y = currenty;
			subTrees.push_back(newpos);
			visitedMap[currentx][currenty] = true;
		}
	}

	// Step 5. Break random walls down
	int wallsLeft = 4 + (rand() % 4);
	int wallsDown = 4 + (rand() % 4);
	while (wallsDown > 0) {
		int xx = rand() % 10;
		int yy = rand() % 10;
		if (m.wallDown(xx, yy, false)) {
			m.setWallDown(xx, yy, false);
			wallsDown--;
		}
	}
	while (wallsLeft > 0) {
		int xx = rand() % 10;
		int yy = rand() % 10;
		if (m.wallRight(xx, yy, false)) {
			m.setWallRight(xx, yy, false);
			wallsLeft--;
		}
	}

	// D O N E

	return m;
}