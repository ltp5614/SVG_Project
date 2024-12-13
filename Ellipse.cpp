#include "Ellipse.h"

Ellipse::Ellipse(int cx, int cy, int rx, int ry, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity)
    : cx(cx), cy(cy), rx(rx), ry(ry), fill(fill), fill_opacity(fill_opacity), stroke(stroke), stroke_width(stroke_width), stroke_opacity(stroke_opacity) {}

void Ellipse::render() const {
    std::cout << "Rendering Ellipse: cx = " << cx << ", cy = " << cy
              << ", rx = " << rx << ", ry = " << ry << ", fill = " << fill
              << ", fill-opacity = " << fill_opacity 
              << ", stroke = " << stroke 
              << ", stroke-width = " << stroke_width 
              << ", stroke-opacity = " << stroke_opacity << std::endl;
}