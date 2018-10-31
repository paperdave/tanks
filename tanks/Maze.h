#pragma once
struct MazeGridCell {
	bool right = false;
	bool down = false;
};

class Maze {
public:
	MazeGridCell grid[10][10];
	Maze();

	bool wallRight(int spaceX, int spaceY, bool def);
	bool wallLeft(int spaceX, int spaceY, bool def);
	bool wallUp(int spaceX, int spaceY, bool def);
	bool wallDown(int spaceX, int spaceY, bool def);

	void setWallRight(int spaceX, int spaceY, bool value);
	void setWallLeft(int spaceX, int spaceY, bool value);
	void setWallUp(int spaceX, int spaceY, bool value);
	void setWallDown(int spaceX, int spaceY, bool value);
};
