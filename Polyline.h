#ifndef POLYLINE_H
#define POLYLINE_H

#include "SVGElements.h"

class Polyline : public SVGElements {
private:
    std::vector<std::pair<int, int>> points;
    std::string fill;
    std::string stroke;
    double fill_opacity;
    int stroke_width;
    double stroke_opacity;

public:
    Polyline(const std::vector<std::pair<int, int>>& points, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity);
    void render() const override;
};

#endif // POLYLINE_H
