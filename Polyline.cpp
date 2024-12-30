#include "Polyline.h"

// Constructor khởi tạo các thuộc tính cho polyline
<<<<<<< HEAD
PolylineSVG::PolylineSVG(const std::vector<std::pair<float, float>>& points, 
=======
PolylineSVG::PolylineSVG(const std::vector<std::pair<int, int>>& points, 
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
                         const std::string& fill, float fill_opacity, 
                         const std::string& stroke, float stroke_width, float stroke_opacity,
                         Transform transform)
            : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform), 
              points(points) {}

// Hàm render để vẽ polyline lên HDC
<<<<<<< HEAD
void PolylineSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const
{
  std::cout << stroke_width << std::endl;
// Kiểm tra nếu cả fill và stroke đều là "none"
    ColorSVG fillColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(fill);
    ColorSVG strokeColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(stroke);


    // Tạo đối tượng Graphics từ HDC
    Gdiplus::Matrix currentMatrix;

    Gdiplus::REAL Elements[6];
    matrix.GetElements(Elements);

    // Tạo một bản sao của ma trận từ cha
    currentMatrix.SetElements(Elements[0], Elements[1],
                          Elements[2], Elements[3],
                          Elements[4], Elements[5]);

    // Chuyển đổi các điểm (x, y) thành kiểu dữ liệu của GDI+
    std::cout << stroke_opacity << std::endl;
=======
void PolylineSVG::render(HDC hdc) const {
    // Phân tích chuỗi màu để tạo đối tượng Color cho fill và stroke
    ColorSVG fillColor = ColorSVG::parseColor(fill);
    ColorSVG strokeColor = ColorSVG::parseColor(stroke);

    // Tạo đối tượng Graphics từ HDC
    Gdiplus::Graphics graphics(hdc);

    // Chuyển đổi các điểm (x, y) thành kiểu dữ liệu của GDI+
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
    std::vector<Gdiplus::Point> gdipPoints;
    for (const auto& point : points) {
        gdipPoints.push_back(Gdiplus::Point(point.first, point.second));
    }

<<<<<<< HEAD
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

    std::cout << stroke_opacity << std::endl;


=======
    // Tạo đối tượng Brush cho màu nền và độ trong suốt (sử dụng nếu bạn muốn fill)
    Gdiplus::SolidBrush fillBrush(Gdiplus::Color(
        static_cast<BYTE>(255 * fill_opacity), 
        fillColor.getRed(), 
        fillColor.getGreen(), 
        fillColor.getBlue()
    ));

    // Tạo đối tượng Pen cho màu viền và độ trong suốt
    Gdiplus::Pen strokePen(Gdiplus::Color(
        static_cast<BYTE>(255 * stroke_opacity), 
        strokeColor.getRed(), 
        strokeColor.getGreen(), 
        strokeColor.getBlue()
    ), stroke_width);

    PointSVG center = getCenter();
    transform.apply(graphics, center);
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f

    // Nếu có màu nền (fill), sẽ vẽ polyline với màu nền
    if (!fill.empty()) {
        graphics.FillPolygon(&fillBrush, &gdipPoints[0], gdipPoints.size());
    }

    // Vẽ polyline (đường gấp khúc) với viền (stroke)
<<<<<<< HEAD
    graphics.DrawLines(&strokePen, &gdipPoints[0], gdipPoints.size());
=======
    graphics.DrawPolygon(&strokePen, &gdipPoints[0], gdipPoints.size());
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
}

// Hàm trả về tọa độ trung tâm của polyline
PointSVG PolylineSVG::getCenter() const {
    // Tính trung bình tọa độ x và y của các điểm
    float sumX = 0, sumY = 0;

    for (const auto& point : points) {
        sumX += point.first;
        sumY += point.second;
    }

    return PointSVG(sumX / points.size(), sumY / points.size());
<<<<<<< HEAD
}
=======
}
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
