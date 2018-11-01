#include "pch.h"
#include "Utility.h"

#include <math.h>
#include <random>
#include <chrono>

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