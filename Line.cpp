// Line.cpp

#include "Line.h"

LineSVG::LineSVG(float x1, float y1, float x2, float y2, 
                 const std::string& fill, float fill_opacity,
                 const std::string& stroke, float stroke_width, float stroke_opacity,
                 Transform transform)
        : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform), 
          x1(x1), y1(y1), x2(x2), y2(y2) {}




void LineSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix, GradientManager gradients) const
{
    // Phân tích chuỗi màu để tạo đối tượng Color cho stroke
    ColorSVG strokeColor = ColorSVG::parseColor(stroke);

    // Tạo đối tượng Graphics
    Gdiplus::Matrix currentMatrix;

    Gdiplus::REAL Elements[6];
    matrix.GetElements(Elements);

    // Tạo một bản sao của ma trận từ cha
    currentMatrix.SetElements(Elements[0], Elements[1],
                          Elements[2], Elements[3],
                          Elements[4], Elements[5]);
    

    // Tạo đối tượng Pen sử dụng các giá trị màu và độ trong suốt
    auto clamp = [](int value, int min, int max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    };

    // Tạo Pen với màu và độ trong suốt đã giới hạn
    Gdiplus::Pen strokePen(
        Gdiplus::Color(
            static_cast<BYTE>(clamp(static_cast<int>(255 * stroke_opacity), 0, 255)), // Alpha
            static_cast<BYTE>(clamp(strokeColor.getRed(), 0, 255)),                  // Red
            static_cast<BYTE>(clamp(strokeColor.getGreen(), 0, 255)),                // Green
            static_cast<BYTE>(clamp(strokeColor.getBlue(), 0, 255))                  // Blue
        ),
        stroke_width
    );

    transform.apply(currentMatrix);
    graphics.SetTransform(&currentMatrix);

    // Vẽ đường thẳng
    graphics.DrawLine(&strokePen, x1, y1, x2, y2);
}