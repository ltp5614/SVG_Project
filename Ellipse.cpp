#include "Ellipse.h"

EllipseSVG::EllipseSVG(float cx, float cy, float rx, float ry, 
                       const std::string& fill, float fill_opacity, 
                       const std::string& stroke, float stroke_width, float stroke_opacity, 
                       Transform transform)
        : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform), 
          cx(cx), cy(cy), rx(rx), ry(ry) {}


void EllipseSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix, GradientManager gradients) const
{
    // Phân tích chuỗi màu để tạo đối tượng Color cho fill và stroke
    ColorSVG fillColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(fill);
    ColorSVG strokeColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(stroke);

    int fillAlpha = (fill == "none" && stroke == "none") ? 255 : static_cast<int>(255 * fill_opacity);
    int strokeAlpha = (fill == "none" && stroke == "none") ? 255 : static_cast<int>(255 * stroke_opacity);

        if (fillAlpha == -1) 
      fillAlpha = 0;
    
    if (strokeAlpha == -1)
      strokeAlpha = 0;


    // Tạo đối tượng Graphics
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

    transform.apply(currentMatrix);

    graphics.SetTransform(&currentMatrix);

    float boxWidth = 2 * rx;  // Chiều rộng = 2 * bán kính
    float boxHeight = 2 * ry; // Chiều cao = 2 * bán kính


    Gdiplus::Brush* fillBrush = nullptr;
    if (fill.find("url(") == 0) {
        // Lấy ID gradient từ `fill="url(#gradient_id)"`
        std::string gradientId = fill.substr(5, fill.size() - 6); // Bỏ "url(" và ")"
        const Gradient* gradient = gradients.getGradient(gradientId); // Hàm getGradientById bạn tự cài đặt
        
        if (gradient) {
            gradient->applyForBrush(matrix, fillBrush, boxWidth, boxHeight); // Áp dụng gradient
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

    // Vẽ ellipse
    graphics.FillEllipse(fillBrush, cx - rx, cy - ry, 2 * rx, 2 * ry);
    graphics.DrawEllipse(strokePen, cx - rx, cy - ry, 2 * rx, 2 * ry);
}