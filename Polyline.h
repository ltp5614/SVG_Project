#ifndef POLYLINE_H
#define POLYLINE_H

#include "SVGElements.h"
#include <vector>

class PolylineSVG : public SVGElements{
private:
    std::vector<std::pair<int, int>> points;

public:
    PolylineSVG(const std::vector<std::pair<int, int>>& points, 
                const std::string& fill, float fill_opacity, 
                const std::string& stroke, float stroke_width, float stroke_opacity,
                Transform transform);
    
    void render(HDC hdc) const override;
    PointSVG getCenter() const override;
};

#endif // POLYLINE_H
