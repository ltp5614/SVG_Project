// Polygon.cpp

#include "Polygon.h"

<<<<<<< HEAD
PolygonSVG::PolygonSVG(const std::vector<std::pair<float, float>>& points, 
=======
PolygonSVG::PolygonSVG(const std::vector<std::pair<int, int>>& points, 
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
                       const std::string& fill, float fill_opacity, 
                       const std::string& stroke, float stroke_width, float stroke_opacity,
                       Transform transform)
          : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform), 
            points(points) {}

<<<<<<< HEAD
void PolygonSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const
{

    std::cout << transform.getTranslateX() << " " << transform.getTranslateY() << std::endl;

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


    // Tạo đối tượng Pen và Brush
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

    std::vector<Gdiplus::Point> gdipPoints;
    for (const auto& point : points) {
        gdipPoints.push_back(Gdiplus::Point(point.first, point.second));
    }


    PointSVG center = getCenter();
    std::cout << center.getX() << center.getY() << std::endl;
    transform.apply(currentMatrix, center);
    graphics.SetTransform(&currentMatrix);

    std::cout << "Fill color: " << fillColor.getRed() << ", " 
          << fillColor.getGreen() << ", " 
          << fillColor.getBlue() << std::endl;

std::cout << "Stroke color: " << strokeColor.getRed() << ", " 
          << strokeColor.getGreen() << ", " 
          << strokeColor.getBlue() << std::endl;




    if (!fill.empty() && fill != "none") {
        graphics.FillPolygon(&fillBrush, &gdipPoints[0], gdipPoints.size());
    }

    // Vẽ đường viền ngôi sao (stroke)
    if (!stroke.empty() && stroke != "none") {
        graphics.DrawPolygon(&strokePen, &gdipPoints[0], gdipPoints.size());
    }
}

PointSVG PolygonSVG::getCenter() const {
    if (points.size() < 3) {
        // Một đa giác hợp lệ phải có ít nhất 3 đỉnh
        std::cerr << "Error: Polygon must have at least 3 points.\n";
        return PointSVG(0, 0);
    }

    float signedArea = 0;
    float cx = 0, cy = 0;

    for (size_t i = 0; i < points.size(); ++i) {
        // Lấy điểm hiện tại và điểm tiếp theo
        const auto& p1 = points[i];
        const auto& p2 = points[(i + 1) % points.size()]; // Đảm bảo vòng lại điểm đầu tiên

        // Tính diện tích từng tam giác
        float a = p1.first * p2.second - p2.first * p1.second;
        signedArea += a;

        // Cộng dồn trọng tâm tạm thời
        cx += (p1.first + p2.first) * a;
        cy += (p1.second + p2.second) * a;
    }

    signedArea *= 0.5f;
    if (signedArea == 0) {
        std::cerr << "Error: Polygon area is zero, cannot compute center.\n";
        return PointSVG(0, 0); // Hoặc xử lý lỗi tùy theo yêu cầu
    }

    // Tính trọng tâm cuối cùng
    cx /= (6 * signedArea);
    cy /= (6 * signedArea);

    return PointSVG(cx, cy);
}

=======
void PolygonSVG::render(HDC hdc) const {
    // Phân tích chuỗi màu để tạo đối tượng Color cho fill và stroke
    ColorSVG fillColor = ColorSVG::parseColor(fill);
    ColorSVG strokeColor = ColorSVG::parseColor(stroke);

    // Tạo đối tượng Graphics
    Gdiplus::Graphics graphics(hdc);

    // Tạo đối tượng Pen và Brush
    Gdiplus::Pen pen(Gdiplus::Color(255 * stroke_opacity, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), stroke_width);
    Gdiplus::SolidBrush brush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));

    // Tạo đối tượng GraphicsPath để vẽ đa giác
    Gdiplus::GraphicsPath path;

    // Thêm các điểm vào GraphicsPath
    if (!points.empty()) {
        path.StartFigure();
        path.AddLine(points[0].first, points[0].second, points[1].first, points[1].second);  // Thêm một đường thẳng đầu tiên

        for (size_t i = 1; i < points.size() - 1; ++i) {
            path.AddLine(points[i].first, points[i].second, points[i + 1].first, points[i + 1].second);
        }

        path.CloseFigure(); // Đóng đa giác
    }

    PointSVG center = getCenter();
    transform.apply(graphics, center);

    // Vẽ đa giác với màu fill và stroke
    graphics.FillPath(&brush, &path); // Vẽ phần fill
    graphics.DrawPath(&pen, &path);   // Vẽ đường viền (stroke)
}

// Hàm trả về tọa độ trung tâm của đa giác
PointSVG PolygonSVG::getCenter() const {
    // Tính trung bình tọa độ x và y của các điểm
    float sumX = 0, sumY = 0;

    for (const auto& point : points) {
        sumX += point.first;
        sumY += point.second;
    }

    // Trả về tọa độ trung tâm
    return PointSVG(sumX / points.size(), sumY / points.size());
}
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
