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


    void render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix, GradientManager gradients) const override;
};

#endif // CIRCLE_H

