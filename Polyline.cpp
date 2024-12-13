#include "Polyline.h"

Polyline::Polyline(const std::vector<std::pair<int, int>>& points, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity)
        : points(points), fill(fill), fill_opacity(fill_opacity), stroke(stroke), stroke_width(stroke_width), stroke_opacity(stroke_opacity) {}

void Polyline::render() const {
    std::cout << "Rendering Polyline with points: ";
    for (const auto& point : points) {
        std::cout << "(" << point.first << ", " << point.second << ") ";
    }
    std::cout << ", fill = " << fill 
         << ", fill-opacity = " << fill_opacity 
		 << ", stroke = " << stroke 
		 << ", stroke-width = " << stroke_width 
		 << ", stroke-opacity = " << stroke_opacity << std::endl;
}