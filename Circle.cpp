// Circle.cpp

#include "Circle.h"

CircleSVG::CircleSVG(float cx, float cy, float r, 
                     const std::string& fill, float fill_opacity,
                     const std::string& stroke, float stroke_width, float stroke_opacity,
                     Transform transform)
        : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform), 
          cx(cx), cy(cy), r(r) {
}


void CircleSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const
{
    // Phân tích chuỗi màu để tạo đối tượng Color cho fill và stroke
// Kiểm tra nếu cả fill và stroke đều là "none"
    ColorSVG fillColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(fill);
    ColorSVG strokeColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(stroke);


    // Tạo đối tượng Graphics
    Gdiplus::Matrix currentMatrix;

    Gdiplus::REAL Elements[6];
    matrix.GetElements(Elements);

    // Tạo một bản sao của ma trận từ cha
    currentMatrix.SetElements(Elements[0], Elements[1],
                          Elements[2], Elements[3],
                          Elements[4], Elements[5]);


    // Tạo đối tượng Pen và Brush sử dụng các giá trị màu và độ trong suốt
    auto clamp = [](int value, int min, int max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    };

    // Tạo SolidBrush với màu đã giới hạn
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

    // Lấy tâm và áp dụng transform
    PointSVG center = getCenter();
    transform.apply(currentMatrix, center);  // Áp dụng phép biến đổi lên ma trận

    // Áp dụng ma trận vào graphics
    graphics.SetTransform(&currentMatrix);

    // Vẽ hình tròn
    graphics.FillEllipse(&fillBrush, cx - r, cy - r, 2 * r, 2 * r);  // Vẽ nền
    graphics.DrawEllipse(&strokePen, cx - r, cy - r, 2 * r, 2 * r);  // Vẽ viền

    std::cout << "Circle rendered successfully.\n\n";
}


PointSVG CircleSVG::getCenter() const {
	return PointSVG(cx, cy);
}
