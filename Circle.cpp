#include "Circle.h"

Circle::Circle(int cx, int cy, int r, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity)
    : cx(cx), cy(cy), r(r), fill(fill), fill_opacity(fill_opacity), stroke(stroke), stroke_width(stroke_width), stroke_opacity(stroke_opacity) {}

void Circle::render() const {
    std::cout << "Rendering Circle: cx = " << cx << ", cy = " << cy
              << ", radius = " << r << ", fill = " << fill 
              << ", fillOpacity = " << fill_opacity 
              << ", stroke = " << stroke 
              << ", stroke-width = " << stroke_width 
              << ", stroke-opacity = " << stroke_opacity << std::endl;
}