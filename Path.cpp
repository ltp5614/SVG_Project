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
              if(str[index] == '-' && index != start)
                break; 
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

void PathSVG::parseFromSVGString(const std::string& svgPath) {
    int i = 0;
    commands.clear();
    char lastCommand = '\0';

    while (i < svgPath.size()) {
        skipWhitespace(svgPath, i);

        // Kiểm tra còn ký tự nào không
        if (i >= svgPath.size()) break;

        // Lấy lệnh
        char command = svgPath[i];
        if (std::isalpha(command)) {
            lastCommand = command;
            ++i;
        } else if (lastCommand == 'M' || lastCommand == 'm') {
            // Mặc định lệnh sau `M` là `L`
            command = (lastCommand == 'M') ? 'L' : 'l';
        } else if (lastCommand == 'Z' || lastCommand == 'z') {
            throw std::runtime_error("Invalid syntax: unexpected parameters after Z");
        } else {
            command = lastCommand;
        }

        // Đọc số lượng tham số cần thiết
        std::vector<float> parameters;
        int numParams = getNumberOfParametersForCommand(command);

        while (numParams > 0 && i < svgPath.size() && !std::isalpha(svgPath[i])) {
            parameters.push_back(parseNumber(svgPath, i));
            skipWhitespace(svgPath, i);

            // Bỏ qua dấu phẩy nếu có
            if (i < svgPath.size() && svgPath[i] == ',') {
                ++i;
            }

            --numParams;

        }

        // Thêm lệnh vào danh sách
        commands.emplace_back(command, parameters);
    }
}

// Hàm lấy số lượng tham số cần thiết cho từng lệnh
int PathSVG::getNumberOfParametersForCommand(char command) const {
    switch (command) {
        case 'M': case 'm': return 2; // MoveTo
        case 'L': case 'l': return 2; // LineTo
        case 'H': case 'h': return 1; // Horizontal LineTo
        case 'V': case 'v': return 1; // Vertical LineTo
        case 'C': case 'c': return 6; // Cubic Bezier Curve
        case 'S': case 's': return 4; // Smooth Cubic Bezier Curve
        case 'Q': case 'q': return 4; // Quadratic Bezier Curve
        case 'T': case 't': return 2; // Smooth Quadratic Bezier Curve
        case 'A': case 'a': return 7; // Elliptical Arc
        case 'Z': case 'z': return 0; // ClosePath
        default:
            throw std::runtime_error("Unsupported command");
    }
}


void PathSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix, GradientManager gradients) const
{
// Kiểm tra nếu cả fill và stroke đều là "none"
    ColorSVG fillColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(fill);
    ColorSVG strokeColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(stroke);


    
    int fillAlpha = (fill == "none" && stroke == "none") ? 255 : static_cast<int>(255 * fill_opacity);
    int strokeAlpha = (fill == "none" && stroke == "none") ? 255 : static_cast<int>(255 * stroke_opacity);

    if (fillAlpha == -1) 
      fillAlpha = 0;
    
    if (strokeAlpha == -1)
      strokeAlpha = 0;




    Gdiplus::Matrix currentMatrix;

    Gdiplus::REAL Elements[6];
    matrix.GetElements(Elements);

    // Tạo một bản sao của ma trận từ cha
    currentMatrix.SetElements(Elements[0], Elements[1],
                          Elements[2], Elements[3],
                          Elements[4], Elements[5]);
    auto clamp = [](int value, int min, int max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    };



    // Dùng GraphicsPath để lưu các đoạn Path
    Gdiplus::GraphicsPath path;
    Gdiplus::PointF currentPoint(0, 0);

    for (const auto& command : commands) {
        char cmd = command.getCommand();
        const auto& params = command.getParameters();

        switch (cmd) {
            case 'M': // Moveto (Absolute)
                currentPoint = Gdiplus::PointF(params[0], params[1]);
                path.StartFigure();
                break;

            case 'm': // Moveto (Relative)
                currentPoint.X += params[0];
                currentPoint.Y += params[1];
                path.StartFigure();
                break;

            case 'L': // Lineto (Absolute)
                path.AddLine(currentPoint, Gdiplus::PointF(params[0], params[1]));
                currentPoint = Gdiplus::PointF(params[0], params[1]);
                break;

            case 'l': // Lineto (Relative)
                path.AddLine(currentPoint, Gdiplus::PointF(currentPoint.X + params[0], currentPoint.Y + params[1]));
                currentPoint.X += params[0];
                currentPoint.Y += params[1];
                break;

            case 'H': // Horizontal lineto (Absolute)
                path.AddLine(currentPoint, Gdiplus::PointF(params[0], currentPoint.Y));
                currentPoint.X = params[0];
                break;

            case 'h': // Horizontal lineto (Relative)
                path.AddLine(currentPoint, Gdiplus::PointF(currentPoint.X + params[0], currentPoint.Y));
                currentPoint.X += params[0];
                break;

            case 'V': // Vertical lineto (Absolute)
                path.AddLine(currentPoint, Gdiplus::PointF(currentPoint.X, params[0]));
                currentPoint.Y = params[0];
                break;

            case 'v': // Vertical lineto (Relative)
                path.AddLine(currentPoint, Gdiplus::PointF(currentPoint.X, currentPoint.Y + params[0]));
                currentPoint.Y += params[0];
                break;
            case 'C': // Cubic Bézier curve (Absolute)
                path.AddBezier(
                    currentPoint,                          // Điểm bắt đầu
                    Gdiplus::PointF(params[0], params[1]), // Điểm điều khiển 1
                    Gdiplus::PointF(params[2], params[3]), // Điểm điều khiển 2
                    Gdiplus::PointF(params[4], params[5])  // Điểm kết thúc
                );
                currentPoint = Gdiplus::PointF(params[4], params[5]);
                break;

            case 'c': // Cubic Bézier curve (Relative)
                path.AddBezier(
                    currentPoint,                          // Điểm bắt đầu
                    Gdiplus::PointF(currentPoint.X + params[0], currentPoint.Y + params[1]), // Điểm điều khiển 1
                    Gdiplus::PointF(currentPoint.X + params[2], currentPoint.Y + params[3]), // Điểm điều khiển 2
                    Gdiplus::PointF(currentPoint.X + params[4], currentPoint.Y + params[5])  // Điểm kết thúc
                );
                currentPoint.X += params[4];
                currentPoint.Y += params[5];
                break;        

            case 'Z': // Closepath (Absolute)
            case 'z': // Closepath (Relative)
                path.CloseFigure();
                break;
              


            default:
                std::cerr << "Unsupported command: " << cmd << std::endl;
        }
    }

    transform.apply(currentMatrix);
    graphics.SetTransform(&currentMatrix);

    
    // Tính toán bounding box của đường dẫn
    Gdiplus::RectF bounds;
    path.GetBounds(&bounds, &matrix);

    // Lấy chiều rộng và chiều cao từ bounding box
    float widthBox = bounds.Width;
    float heightBox = bounds.Height;



    Gdiplus::Brush* fillBrush = nullptr;
    if (fill.find("url(") == 0) {
        // Lấy ID gradient từ `fill="url(#gradient_id)"`
        std::string gradientId = fill.substr(5, fill.size() - 6); // Bỏ "url(" và ")"
        const Gradient* gradient = gradients.getGradient(gradientId); // Hàm getGradientById bạn tự cài đặt
        
        if (gradient) {
            gradient->applyForBrush(matrix, fillBrush, widthBox, heightBox); // Áp dụng gradient
        }
     
    }

    if (!fillBrush) {
        // Nếu không có gradient, sử dụng màu solid

        ColorSVG fillColor = ColorSVG::parseColor(fill);
        fillBrush = new Gdiplus::SolidBrush(
            Gdiplus::Color(
                static_cast<BYTE>(clamp(fillAlpha, 0, 255)), // Alpha
                static_cast<BYTE>(clamp(fillColor.getRed(), 0, 255)),  // Red
                static_cast<BYTE>(clamp(fillColor.getGreen(), 0, 255)),  // Green
                static_cast<BYTE>(clamp(fillColor.getBlue(), 0, 255))  // Blue
            )
        );
    }

    // Xử lý stroke
    Gdiplus::Pen* strokePen = nullptr;

    if (!strokePen) {
        // Nếu không có gradient, sử dụng màu solid


        ColorSVG strokeColor = ColorSVG::parseColor(stroke);
        strokePen = new Gdiplus::Pen(
            Gdiplus::Color(
                static_cast<BYTE>(clamp(strokeAlpha, 0, 255)), // Alpha
                static_cast<BYTE>(clamp(strokeColor.getRed(), 0, 255)),  // Red
                static_cast<BYTE>(clamp(strokeColor.getGreen(), 0, 255)),  // Green
                static_cast<BYTE>(clamp(strokeColor.getBlue(), 0, 255))  // Blue
            ),
            stroke_width
        );
    }


    // Vẽ nền (fill)
    graphics.FillPath(fillBrush, &path);

    // Vẽ viền (stroke)
    graphics.DrawPath(strokePen, &path);
}