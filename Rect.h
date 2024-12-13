#ifndef RECT_H
#define RECT_H

#include "SVGElements.h"

class Rect : public SVGElements {
private:
    int x, y, width, height;
    std::string fill;
    double fill_opacity;
    std::string stroke;
    int stroke_width;
    
    

public:
    Rect(int x, int y, int width, int height, const std::string& fill, double fill_opacity, const std::string& stroke,  int stroke_width);
    void render() const override;
};

#endif // RECT_H
