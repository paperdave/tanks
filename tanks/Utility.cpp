#include "pch.h"
#include "Utility.h"

#include <math.h>
#include <random>
#include <chrono>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>

#define PI           3.14159265358979323846

using namespace std::chrono;
std::random_device rd;

double toRad(double deg) {
	return 2 * PI * (deg / 360);
}
double lengthdir_x(double length, double dir) {
	return cos(toRad(dir)) * length;
}
double lengthdir_y(double length, double dir) {
	return sin(toRad(dir)) * length;
}

double sign(double x) {
	return x > 0 ? 1 : (x < 0 ? -1 : 0);
}
double wave(double from, double to, double duration, double offset) {
	double a4 = (to - from) * 0.5;
	int current_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	return from + a4 + sin((((current_time * 0.01) + duration * offset) / duration) * (PI * 2)) * a4;
}

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str) {
	std::vector<std::string> result;
	std::string line;
	std::getline(str, line);

	std::stringstream  lineStream(line);
	std::string  cell;

	while (std::getline(lineStream, cell, ','))
	{
		result.push_back(cell);
	}
	// This checks for a trailing comma with no data after it.
	if (!lineStream && cell.empty())
	{
		// If there was a trailing comma then add an empty element.
		result.push_back("");
	}
	return result;
}

bool str2int(int &i, char const *s) {
	std::stringstream ss(s);
	ss >> i;
	if (ss.fail()) {
		// not an integer
		return false;
	}
	return true;
}

bool util_file_exists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}
