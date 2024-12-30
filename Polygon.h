#ifndef POLYGON_H
#define POLYGON_H

#include "SVGElements.h"
#include <vector>

class PolygonSVG : public SVGElements {
private:
<<<<<<< HEAD
    std::vector<std::pair<float, float>> points;

public:
    PolygonSVG(const std::vector<std::pair<float, float>>& points, 
               const std::string& fill, float fill_opacity, 
               const std::string& stroke, float stroke_width, float stroke_opacity,
               Transform transform);

    void render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const override;
=======
    std::vector<std::pair<int, int>> points;

public:
    PolygonSVG(const std::vector<std::pair<int, int>>& points, 
               const std::string& fill, float fill_opacity, 
               const std::string& stroke, float stroke_width, float stroke_opacity,
               Transform transform);
    
    void render(HDC hdc) const override;
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
    PointSVG getCenter() const override;
};

#endif // POLYGON_H
