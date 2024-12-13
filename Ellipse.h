#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "SVGElements.h"

class Ellipse : public SVGElements {
private:
    int cx, cy;
    int rx, ry;
    std::string fill, stroke;
    int stroke_width;
    double stroke_opacity, fill_opacity;

public:
    Ellipse(int cx, int cy, int rx, int ry, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity);
    void render() const override;
};

#endif // ELLIPSE_H
