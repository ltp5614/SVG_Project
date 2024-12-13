// Line.cpp

#include "Line.h"

LineSVG::LineSVG(float x1, float y1, float x2, float y2, 
                 const std::string& fill, float fill_opacity,
                 const std::string& stroke, float stroke_width, float stroke_opacity,
                 Transform transform)
        : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform), 
          x1(x1), y1(y1), x2(x2), y2(y2) {}

void LineSVG::render(HDC hdc) const 
{
    // Phân tích chuỗi màu để tạo đối tượng Color cho stroke
    ColorSVG strokeColor = ColorSVG::parseColor(stroke);

    // Tạo đối tượng Graphics
    Gdiplus::Graphics graphics(hdc);

    // Tạo đối tượng Pen sử dụng các giá trị màu và độ trong suốt
    Gdiplus::Pen pen(Gdiplus::Color(255 * stroke_opacity, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), stroke_width);

    PointSVG center = getCenter();
    transform.apply(graphics, center);

    // Vẽ đường thẳng
    graphics.DrawLine(&pen, x1, y1, x2, y2);
}

PointSVG LineSVG::getCenter() const {
	return PointSVG((x1 + x2) / 2, (y1 + y2) / 2);
}