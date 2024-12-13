#include "Path.h"
#include <algorithm>
#include <limits>

PathSVG::PathSVG(const std::string& pointsData, 
                 const std::string& fill, float fill_opacity,
                 const std::string& stroke, float stroke_width, float stroke_opacity, 
                 Transform transform)
        : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform) {
    
    parseFromSVGString(pointsData);  // Gọi hàm phân tích chuỗi SVG vào commands
}

void PathSVG::skipWhitespace(const std::string& str, int& index) const {
    while (index < str.size() && std::isspace(str[index])) {
        ++index;
    }
}

    // Hàm đọc một số (float)
float PathSVG::parseNumber(const std::string& str, int& index) const {
    skipWhitespace(str, index);
    int start = index;
    while (index < str.size() &&
            (std::isdigit(str[index]) || str[index] == '.' || str[index] == '-' || str[index] == '+')) {
        ++index;
    }
    if (start == index) throw std::runtime_error("Expected a number");
    return std::stof(str.substr(start, index - start));
}

void PathSVG::calculateArcParameters(const Gdiplus::PointF& currentPoint, const Gdiplus::PointF& endPoint, 
                                  float rx, float ry, float xAxisRotation, int largeArcFlag, int sweepFlag, 
                                  float& cx, float& cy, float& theta1, float& deltaTheta) const {
    // (Tính toán theo công thức SVG Arc, không mở rộng ở đây)
}

std::vector<Gdiplus::PointF> PathSVG::calculateBezierForArc(float cx, float cy, float rx, float ry, 
                                                            float xAxisRotation, float thetaStart, float thetaEnd) const {
    std::vector<Gdiplus::PointF> points(4);

    // (Tính toán các điểm control và anchor của Bézier từ tham số cung)

    return points;
}

void PathSVG::renderArc(Gdiplus::Graphics& graphics, Gdiplus::GraphicsPath& path, 
                     Gdiplus::PointF& currentPoint, const std::vector<float>& params) const {

    float rx = params[0];
    float ry = params[1];
    float xAxisRotation = params[2];
    int largeArcFlag = static_cast<int>(params[3]);
    int sweepFlag = static_cast<int>(params[4]);
    Gdiplus::PointF endPoint(params[5], params[6]);

    if (rx == 0 || ry == 0) {
        path.AddLine(currentPoint, endPoint);
        currentPoint = endPoint;
        return;
    }

    // Tính toán tọa độ tâm, góc bắt đầu và góc quét
    float cx, cy, theta1, deltaTheta;
    calculateArcParameters(currentPoint, endPoint, rx, ry, xAxisRotation, largeArcFlag, sweepFlag, 
                           cx, cy, theta1, deltaTheta);

    // Chia cung thành các đoạn nhỏ hơn 90° và thêm vào Path
    int numSegments = static_cast<int>(ceil(fabs(deltaTheta) / (M_PI / 2)));
    float segmentTheta = deltaTheta / numSegments;

    for (int i = 0; i < numSegments; ++i) {
        float thetaStart = theta1 + i * segmentTheta;
        float thetaEnd = thetaStart + segmentTheta;

        auto bezierPoints = calculateBezierForArc(cx, cy, rx, ry, xAxisRotation, thetaStart, thetaEnd);
        path.AddBezier(bezierPoints[0], bezierPoints[1], bezierPoints[2], bezierPoints[3]);
    }

    currentPoint = endPoint;
}


void PathSVG::addCommand(const PathCommand& command) {
        commands.push_back(command);
}

// Lấy danh sách các lệnh
const std::vector<PathCommand>& PathSVG::getCommands() const {
    return commands;
}

// Chuyển toàn bộ path thành chuỗi SVG
std::string PathSVG::toSVGString() const {
    std::ostringstream oss;

    for (int i = 0; i < commands.size(); ++i) {
        oss << commands[i].tostring();
        if (i < commands.size() - 1) oss << " ";
    }

    return oss.str();
}

// Xóa toàn bộ path
void PathSVG::clear() {
    commands.clear();
}

// Phân tích chuỗi SVG path và nạp vào Path
void PathSVG::parseFromSVGString(const std::string& svgPath) {
    int i = 0;

    Gdiplus::PointF lastPoint(0, 0); // Điểm trước đó (Mặc định ban đầu)

    while (i < svgPath.size()) {
        skipWhitespace(svgPath, i);

        // Lấy lệnh (ký tự đầu tiên)
        if (i >= svgPath.size()) break;
        char command = svgPath[i];

        if (!std::isalpha(command)) {
            throw std::runtime_error("Expected a command");
        }
        
        ++i;

        // Đọc các tham số
        std::vector<float> parameters;

        if (command != 'Z' && command != 'z') { // Z không có tham số
            while (i < svgPath.size() && !std::isalpha(svgPath[i])) {
                parameters.push_back(parseNumber(svgPath, i));
                skipWhitespace(svgPath, i);

                // Nếu có dấu phẩy, bỏ qua
                if (i < svgPath.size() && svgPath[i] == ',') {
                    ++i;
                }
            }
        }

        commands.emplace_back(command, parameters);
    }
}

void PathSVG::render(HDC hdc) const {

    ColorSVG fillColor = ColorSVG::parseColor(fill);
    ColorSVG strokeColor = ColorSVG::parseColor(stroke);

    Gdiplus::Graphics graphics(hdc);
    Gdiplus::SolidBrush fillBrush(Gdiplus::Color(255 * fill_opacity, fillColor.getRed(), fillColor.getGreen(), fillColor.getBlue()));

    // Tạo đối tượng Pen cho màu viền và độ trong suốt
    Gdiplus::Pen strokePen(Gdiplus::Color(255 * stroke_opacity, strokeColor.getRed(), strokeColor.getGreen(), strokeColor.getBlue()), stroke_width);


    // Dùng GraphicsPath để lưu các đoạn Path
    Gdiplus::GraphicsPath path;

    Gdiplus::PointF currentPoint(0, 0);

    for (const auto& command : commands) {
        char cmd = command.getCommand();
        const auto& params = command.getParameters();

        switch (cmd) {
        // Moveto
        case 'M' : case 'm' : {
            currentPoint = Gdiplus::PointF(params[0], params[1]);
            path.StartFigure(); // Bắt đầu một hình mới
            break;
        }
        
        // Lineto
        case 'L' : case 'l' : {
            path.AddLine(currentPoint, Gdiplus::PointF(params[0], params[1]));
            currentPoint = Gdiplus::PointF(params[0], params[1]);
            break;
        }
        
	    // Horizontal lineto
        case 'H' : case 'h' : {
            path.AddLine(currentPoint, Gdiplus::PointF(params[0], currentPoint.Y));
            currentPoint.X = params[0];
            break;
	    }

        // Vertical lineto
        case 'V' : case 'v' : {
            path.AddLine(currentPoint, Gdiplus::PointF(currentPoint.X, params[0]));
            currentPoint.Y = params[0];
            break;
	    }

        // Cubic Bézier curve
        case 'C' : case 'c' : {
            path.AddBezier(currentPoint, 
                            Gdiplus::PointF(params[0], params[1]), 
                            Gdiplus::PointF(params[2], params[3]), 
                            Gdiplus::PointF(params[4], params[5]));
            currentPoint = Gdiplus::PointF(params[4], params[5]);
            break;
        }

        // Quadratic Bézier curve
        case 'Q' : case 'q' : {
            path.AddBezier(currentPoint,
                            Gdiplus::PointF((2 * params[0] + currentPoint.X) / 3, 
                                            (2 * params[1] + currentPoint.Y) / 3), 
                            Gdiplus::PointF((2 * params[0] + params[2]) / 3, 
                                            (2 * params[1] + params[3]) / 3), 
                            Gdiplus::PointF(params[2], params[3]));
            currentPoint = Gdiplus::PointF(params[2], params[3]);
            break;
        }

        // Elliptical arc
        case 'A' : case 'a' : {
            renderArc(graphics, path, currentPoint, params);
            break;
        }
        
        // Closepath
        case 'Z' : case 'z' : {
            path.CloseFigure();
            break;
        }

        default: {
            std::cout << "Unknown command: " << cmd << std::endl;
        }
        }
    }

    PointSVG center = getCenter();
    transform.apply(graphics, center);

    // Vẽ nền (fill)
    graphics.FillPath(&fillBrush, &path);

    // Vẽ viền (stroke)
    graphics.DrawPath(&strokePen, &path);

    std::cout << "Render path" << std::endl;
}

PointSVG PathSVG::getCenter() const {
    float sumX = 0;
    float sumY = 0;
    int pointCount = 0;

    for (const auto& command : commands) {
        const auto& params = command.getParameters();

        // Duyệt qua từng cặp (x, y) trong danh sách tham số
        for (size_t i = 0; i < params.size(); i += 2) {
            sumX += params[i];        // Tổng các giá trị x
            sumY += params[i + 1];    // Tổng các giá trị y
            pointCount++;             // Đếm số điểm
        }
    }

    // Tính tọa độ tâm bằng trung bình cộng của x và y
    if (pointCount == 0) {
        return PointSVG(0, 0); // Trả về tâm mặc định nếu không có điểm nào
    }

    return PointSVG(sumX / pointCount, sumY / pointCount);
}