#ifndef LINE_H
#define LINE_H

#include "SVGElements.h"

class Line : public SVGElements {
private:
    int x1, y1, x2, y2;
    std::string stroke;
    int stroke_width;
    double stroke_opacity;

public:
    Line(int x1, int y1, int x2, int y2, const std::string& stroke, int stroke_width, double stroke_opacity);
    void render() const override;
};

#endif // LINE_H
