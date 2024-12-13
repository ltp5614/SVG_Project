// Polygon.cpp

#include "Polygon.h"

PolygonSVG::PolygonSVG(const std::vector<std::pair<int, int>>& points, 
                       const std::string& fill, float fill_opacity, 
                       const std::string& stroke, float stroke_width, float stroke_opacity,
                       Transform transform)
          : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform), 
            points(points) {}

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