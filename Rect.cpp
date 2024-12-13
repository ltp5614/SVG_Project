#include "Rect.h"

Rect::Rect(int x, int y, int width, int height, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width)
    : x(x), y(y), width(width), height(height), fill(fill), fill_opacity(fill_opacity), stroke(stroke), stroke_width(stroke_width) {}

void Rect::render() const {
    std::cout << "Rendering Rectangle: x = " << x << ", y = " << y
         << ", width = " << width << ", height = " << height
         << ", fill = " << fill  
         << ", fill opacity = " << fill_opacity 
         << ", stroke = " << stroke
         << ", stroke width = " << stroke_width << std::endl;
}