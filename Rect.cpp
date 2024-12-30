#include "Rect.h"

// Constructor definition
RectSVG::RectSVG(float x, float y, float width, float height, 
                 const std::string& fill, float fill_opacity, 
                 const std::string& stroke, float stroke_width, float stroke_opacity,
                 Transform transform)
        :SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform),
         x(x), y(y), width(width), height(height) {}

<<<<<<< HEAD
void RectSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const
{
// Kiểm tra nếu cả fill và stroke đều là "none"
    ColorSVG fillColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(fill);
    ColorSVG strokeColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(stroke);


    // Create GDI+ Graphics object
    Gdiplus::Matrix currentMatrix;

    Gdiplus::REAL Elements[6];
    matrix.GetElements(Elements);

    // Tạo một bản sao của ma trận từ cha
    currentMatrix.SetElements(Elements[0], Elements[1],
                          Elements[2], Elements[3],
                          Elements[4], Elements[5]);


    // Create Pen (stroke) and SolidBrush (fill) for GDI+ rendering
    auto clamp = [](int value, int min, int max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    };
    int fillAlpha = (fill == "none" && stroke == "none") ? 255 : static_cast<int>(255 * fill_opacity);
    int strokeAlpha = (fill == "none" && stroke == "none") ? 255 : static_cast<int>(255 * stroke_opacity);

    // Tạo SolidBrush với màu đã giới hạn và độ trong suốt
    Gdiplus::SolidBrush fillBrush(
        Gdiplus::Color(
            static_cast<BYTE>(clamp(fillAlpha, 0, 255)), // Alpha (độ trong suốt)
            static_cast<BYTE>(clamp(fillColor.getRed(), 0, 255)),  // Red
            static_cast<BYTE>(clamp(fillColor.getGreen(), 0, 255)),  // Green
            static_cast<BYTE>(clamp(fillColor.getBlue(), 0, 255))  // Blue
        )
    );

    // Tạo Pen với màu và độ trong suốt đã giới hạn
    Gdiplus::Pen strokePen(
        Gdiplus::Color(
            static_cast<BYTE>(clamp(strokeAlpha, 0, 255)), // Alpha (độ trong suốt)
            static_cast<BYTE>(clamp(strokeColor.getRed(), 0, 255)), // Red
            static_cast<BYTE>(clamp(strokeColor.getGreen(), 0, 255)), // Green
            static_cast<BYTE>(clamp(strokeColor.getBlue(), 0, 255)) // Blue
        ),
        stroke_width
    );

    PointSVG center = getCenter();
    transform.apply(currentMatrix, center);
    graphics.SetTransform(&currentMatrix);

    // Draw the filled rectangle
    graphics.FillRectangle(&fillBrush, x, y, width, height);

    // Draw the rectangle outline (stroke)
    graphics.DrawRectangle(&strokePen, x, y, width, height);
}


PointSVG RectSVG::getCenter() const {
	return PointSVG(x + width / 2, y + height / 2);
}
=======
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
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
