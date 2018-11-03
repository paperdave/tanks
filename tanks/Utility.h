#pragma once
#include <vector>
#include <iostream>

double toRad(double deg);
double lengthdir_x(double length, double dir);
double lengthdir_y(double length, double dir);

double sign(double x);
double wave(double from, double to, double duration, double offset);

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str);
bool str2int(int &i, char const *s);
