#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "SVGElements.h"

class EllipseSVG : public SVGElements{
private:
    float cx, cy, rx, ry;

public:
    EllipseSVG(float cx, float cy, float rx, float ry, 
               const std::string& fill, float fill_opacity, 
               const std::string& stroke, float stroke_width, float stroke_opacity,
               Transform transform);

    void render(HDC hdc) const override;
    PointSVG getCenter() const override;
};

#endif // ELLIPSE_H
