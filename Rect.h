#ifndef RECT_H
#define RECT_H

#include "SVGElements.h"

class RectSVG : public SVGElements {
private:
    float x, y, width, height;  // Position and size of the rectangle

public:
    // Constructor to initialize the rectangle attributes
    RectSVG(float x, float y, float width, float height, 
            const std::string& fill, float fill_opacity, 
            const std::string& stroke, float stroke_width, float stroke_opacity,
            Transform transform);

    // Render method to draw the rectangle
    void render(HDC hdc) const override;
    PointSVG getCenter() const override;
};

#endif // RECT_H
