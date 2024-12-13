#include "Path.h"

Path::Path(const std::vector<std::pair<int, int> >& points, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity) 
    : points(points), fill(fill), fill_opacity(fill_opacity), stroke(stroke), stroke_width(stroke_width), stroke_opacity(stroke_opacity) {}

void Path::render() const  {
    std::cout << "Rendering Path with points: ";
    for (const auto& point : points) {
        std::cout << "(" << point.first << ", " << point.second << ") ";
    }

    std::cout << ", fill = " << fill 
         << ", fill-opacity = " << fill_opacity 
         << ", stroke = " << stroke
         << ", stroke-width = " << stroke_width
         << ", stroke-opacity = " << stroke_opacity << std::endl;
}

std::vector<std::pair<int, int>> parsePathData(const std::string& d) {
    std::vector<std::pair<int, int>> points;
    std::istringstream ss(d);
    char command;
    float x = 0, y = 0;

    while (ss >> command) {
        if (command == 'M' || command == 'L') {
            float newX, newY;
            ss >> newX >> newY;

            points.emplace_back(static_cast<int>(newX), static_cast<int>(newY));

            x = newX;
            y = newY;
        }
    }

    return points;
}
