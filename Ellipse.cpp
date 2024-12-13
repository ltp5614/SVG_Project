#include "Ellipse.h"

EllipseSVG::EllipseSVG(float cx, float cy, float rx, float ry, 
                       const std::string& fill, float fill_opacity, 
                       const std::string& stroke, float stroke_width, float stroke_opacity, 
                       Transform transform)
        : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform), 
          cx(cx), cy(cy), rx(rx), ry(ry) {}


void EllipseSVG::render(HDC hdc) const {
    // Phân tích chuỗi màu để tạo đối tượng Color cho fill và stroke
    ColorSVG fillColor = ColorSVG::parseColor(fill);
    ColorSVG strokeColor = ColorSVG::parseColor(stroke);

    // Tạo đối tượng Graphics
    Gdiplus::Graphics graphics(hdc);

    // Tạo đối tượng Pen và Brush sử dụng các giá trị màu và độ trong suốt
    Gdiplus::Pen pen(Gdiplus::Color(255 * stroke_opacity, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), stroke_width);
    Gdiplus::SolidBrush brush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));

    PointSVG center = getCenter();
    transform.apply(graphics, center);

    // Vẽ ellipse
    graphics.FillEllipse(&brush, cx - rx, cy - ry, 2 * rx, 2 * ry);
    graphics.DrawEllipse(&pen, cx - rx, cy - ry, 2 * rx, 2 * ry);
}

PointSVG EllipseSVG::getCenter() const {
	return PointSVG(cx, cy);
}