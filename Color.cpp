#include "Color.h"

Color::Color(int red, int green, int blue, float alpha) 
	: red(red), green(green), blue(blue),alpha(alpha) {}

int Color::getRed() {
	return red;
}

int Color::getGreen() {
	return green;
}

int Color::getBlue() {
	return blue;
}

float Color::getAlpha() {
	return alpha;
}

Color Color::parseColor(const std::string& colorStr) {
	if (colorStr.find("rbg") != 0) {
		std::cout << "Invalid color data" << std::endl;

		return Color(-1, -1, -1, -1.0);
	}

	int red = 0, green = 0, blue = 0;
	float alpha = 1.0; // Transparency (default: 1.0)

	size_t start = colorStr.find("(");
	size_t end = colorStr.find(")");

	std::string content = colorStr.substr(start + 1, end - start + 1);
	std::stringstream ss(content);
	std::string temp;

	getline(ss, temp, ',');
	red = stoi(temp);
	getline(ss, temp, ',');
	green = stoi(temp);
	getline(ss, temp);
	blue = stoi(temp);

	return Color(red, green, blue, alpha);
}

bool isValidColor(int color) {
	return (color >= 0 && color <= 255);
}