#ifndef POLYGON_H
#define POLYGON_H

#include "SVGElements.h"
#include <vector>

class PolygonSVG : public SVGElements {
private:
    std::vector<std::pair<float, float>> points;

public:
    PolygonSVG(const std::vector<std::pair<float, float>>& points, 
               const std::string& fill, float fill_opacity, 
               const std::string& stroke, float stroke_width, float stroke_opacity,
               Transform transform);

    void render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix, GradientManager gradients) const override;
};

#endif // POLYGON_H
