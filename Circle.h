#ifndef CIRCLE_H
#define CIRCLE_H

#include "SVGElements.h"

class CircleSVG : public SVGElements{
private:
    float cx, cy, r;

public:
    CircleSVG(float cx, float cy, float r,
              const std::string& fill, float fill_opacity,
              const std::string& stroke, float stroke_width, float stroke_opacity,
              Transform transform);
<<<<<<< HEAD


    void render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const override;
=======
    
    void render(HDC hdc) const override;  // Ghi đè phương thức render
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
    PointSVG getCenter() const override;  // Ghi đè phương thức getCenter
};

#endif // CIRCLE_H

