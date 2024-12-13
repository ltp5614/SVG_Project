#ifndef POLYGON_H
#define POLYGON_H

#include "SVGElements.h"

class Polygon : public SVGElements
{
private:
    std::vector<std::pair<int, int>> points;
    std::string stroke;
    std::string fill;
    double fill_opacity;
    int stroke_width;
    double stroke_opacity;

public:
    Polygon(const std::vector<std::pair<int, int>>& points, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity);
    void render() const override;
};

#endif // POLYGON_H
