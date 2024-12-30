#ifndef LINE_H
#define LINE_H

#include "SVGElements.h"

class LineSVG : public SVGElements {
private:
    float x1, y1, x2, y2;

public:
    LineSVG(float x1, float y1, float x2, float y2, 
            const std::string& fill, float fill_opacity,
            const std::string& stroke, float stroke_width, float stroke_opacity,
            Transform transform);

<<<<<<< HEAD

    void render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const override;
    PointSVG getCenter() const;
=======
    void render(HDC hdc) const override;
    PointSVG getCenter() const override;
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f

};

#endif // LINE_H
