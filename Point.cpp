#include "Point.h"

PointSVG::PointSVG() : x(0), y(0) {}

PointSVG::PointSVG(float x, float y) : x(x), y(y) {}

float PointSVG::getX() { return x; }
float PointSVG::getY() { return y; }

void PointSVG::setX(float x) { this->x = x; }
void PointSVG::setY(float y) { this->y = y; }
