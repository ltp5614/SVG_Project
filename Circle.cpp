// Circle.cpp

#include "Circle.h"

CircleSVG::CircleSVG(float cx, float cy, float r, 
                     const std::string& fill, float fill_opacity,
                     const std::string& stroke, float stroke_width, float stroke_opacity,
                     Transform transform)
        : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform), 
          cx(cx), cy(cy), r(r) {}


void CircleSVG::render(HDC hdc) const {
    ColorSVG fillColor = ColorSVG::parseColor(fill);
    ColorSVG strokeColor = ColorSVG::parseColor(stroke);

    Gdiplus::Graphics graphics(hdc);

    Gdiplus::SolidBrush fillBrush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));

    // Tạo đối tượng Pen cho màu viền và độ trong suốt
    Gdiplus::Pen strokePen(Gdiplus::Color(255 * stroke_opacity, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), stroke_width);

    PointSVG center = getCenter();
    transform.apply(graphics, center);
 
    // Vẽ hình tròn (CircleSVG)
    graphics.FillEllipse(&fillBrush, cx - r, cy - r, 2 * r, 2 * r);  // Vẽ nền
    graphics.DrawEllipse(&strokePen, cx - r, cy - r, 2 * r, 2 * r);  // Vẽ viền
}

PointSVG CircleSVG::getCenter() const {
	return PointSVG(cx, cy);
}