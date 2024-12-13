#ifndef CIRCLE_H
#define CIRCLE_H

#include "SVGElements.h"

class Circle : public SVGElements {
private:
    int cx, cy, r;
    std::string fill, stroke;
    int stroke_width;
    double stroke_opacity, fill_opacity;

public:
    Circle(int cx, int cy, int r, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity);
    void render() const override;
};

#endif // CIRCLE_H
