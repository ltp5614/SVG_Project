#include "Rect.h"

// Constructor definition
RectSVG::RectSVG(float x, float y, float width, float height, 
                 const std::string& fill, float fill_opacity, 
                 const std::string& stroke, float stroke_width, float stroke_opacity,
                 Transform transform)
        :SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform),
         x(x), y(y), width(width), height(height) {}

void RectSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix, GradientManager gradients) const
{
    std::cout << fill << " " << stroke << std::endl;
// Kiểm tra nếu cả fill và stroke đều là "none"
    ColorSVG fillColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(fill);
    ColorSVG strokeColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(stroke);

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


    if (fillAlpha == -1) 
      fillAlpha = 0;
    
    if (strokeAlpha == -1)
      strokeAlpha = 0;

    transform.apply(currentMatrix);
    graphics.SetTransform(&currentMatrix);



    Gdiplus::Brush* fillBrush = nullptr;
    if (fill.find("url(") == 0) {
        // Lấy ID gradient từ `fill="url(#gradient_id)"`
        std::string gradientId = fill.substr(5, fill.size() - 6); // Bỏ "url(" và ")"
        const Gradient* gradient = gradients.getGradient(gradientId); // Hàm getGradientById bạn tự cài đặt
        
        if (gradient) {
            gradient->applyForBrush(matrix, fillBrush, width, height); // Áp dụng gradient
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
    // Draw the filled rectangle
    graphics.FillRectangle(fillBrush, x, y, width, height);

    // Draw the rectangle outline (stroke)
    graphics.DrawRectangle(strokePen, x, y, width, height);
}
