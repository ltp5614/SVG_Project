#include "Rect.h"

// Constructor definition
RectSVG::RectSVG(float x, float y, float width, float height, 
                 const std::string& fill, float fill_opacity, 
                 const std::string& stroke, float stroke_width, float stroke_opacity,
                 Transform transform)
        :SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform),
         x(x), y(y), width(width), height(height) {}

// Render method definition
void RectSVG::render(HDC hdc) const {
    // Parse color for fill and stroke
    ColorSVG fillColor = ColorSVG::parseColor(fill);  // Assuming Color::parseColor() returns a Color object
    ColorSVG strokeColor = ColorSVG::parseColor(stroke);

    // Create GDI+ Graphics object
    Gdiplus::Graphics graphics(hdc);

    // Create Pen (stroke) and SolidBrush (fill) for GDI+ rendering
    Gdiplus::Pen pen(Gdiplus::Color(255, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), stroke_width);
    Gdiplus::SolidBrush brush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));

    PointSVG center = getCenter();
    transform.apply(graphics, center);

    // Draw the filled rectangle
    graphics.FillRectangle(&brush, x, y, width, height);

    // Draw the rectangle outline (stroke)
    graphics.DrawRectangle(&pen, x, y, width, height);
}

PointSVG RectSVG::getCenter() const {
	return PointSVG(x + width / 2, y + height / 2);
}