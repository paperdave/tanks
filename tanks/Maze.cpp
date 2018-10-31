#include "pch.h"
#include "Maze.h"

Maze::Maze() {
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 10; j++) {
			grid[i][j].down = true;
			grid[i][j].right = true;
		}
	}
}
bool Maze::wallRight(int spaceX, int spaceY, bool def = true) {
	if (spaceY >= 9) return def;
	if (spaceX > 9) return def;
	if (spaceY < 0) return def;
	if (spaceX < 0) return def;

	return grid[spaceX][spaceY].right;
}
bool Maze::wallDown(int spaceX, int spaceY, bool def = true) {
	if (spaceX > 9) return def;
	if (spaceY >= 9) return def;
	if (spaceY < 0) return def;
	if (spaceX < 0) return def;

	return grid[spaceX][spaceY].down;
}
bool Maze::wallLeft(int spaceX, int spaceY, bool def = true) {
	if (spaceX > 9) return def;
	if (spaceY > 9) return def;
	if (spaceY < 0) return def;
	if (spaceX <= 0) return def;

	return grid[spaceX - 1][spaceY].right;
}
bool Maze::wallUp(int spaceX, int spaceY, bool def = true) {
	if (spaceX > 9) return def;
	if (spaceY > 9) return def;
	if (spaceY < 0) return def;
	if (spaceX <= 0) return def;

	return grid[spaceX][spaceY - 1].down;
}
void Maze::setWallRight(int spaceX, int spaceY, bool value = true) {
	if (spaceX >= 9) return;
	if (spaceY > 9) return;
	if (spaceY < 0) return;
	if (spaceX < 0) return;

	grid[spaceX][spaceY].right = value;
}
void Maze::setWallDown(int spaceX, int spaceY, bool value = true) {
	if (spaceX > 9) return;
	if (spaceY >= 9) return;
	if (spaceY < 0) return;
	if (spaceX < 0) return;

	grid[spaceX][spaceY].down = value;
}
void Maze::setWallLeft(int spaceX, int spaceY, bool value = true) {
	if (spaceX > 9) return;
	if (spaceY > 9) return;
	if (spaceY < 0) return;
	if (spaceX <= 0) return;

	grid[spaceX - 1][spaceY].right = value;
}
void Maze::setWallUp(int spaceX, int spaceY, bool value = true) {
	if (spaceX > 9) return;
	if (spaceY > 9) return;
	if (spaceX < 0) return;
	if (spaceY <= 0) return;

	grid[spaceX][spaceY - 1].down = value;
}