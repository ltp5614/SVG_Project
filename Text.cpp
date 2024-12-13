#include "Text.h"

TextSVG::TextSVG(float x, float y, float dx, float dy,
                 float font_size, const std::string& content, const std::wstring& font,
                 const std::string& fill, float fill_opacity, 
                 const std::string& stroke, float stroke_width, float stroke_opacity,
                 Transform transform)
        : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform),
          x(x), y(y), dx(dx), dy(dy), font_size(font_size), content(content), font(font) {}

void TextSVG::render(HDC hdc) const {
    // Convert the fill color string into a Color object (assuming you use Color class for handling colors)
    ColorSVG textColor = ColorSVG::parseColor(fill);

    // Khởi tạo đối tượng Graphics
    Gdiplus::Graphics graphics(hdc); // hdc là tham số đã có trong hàm của bạn

    // Lấy DPI của màn hình
    float dpiX = graphics.GetDpiX();
    float dpiY = graphics.GetDpiY();

    // Điều chỉnh kích thước font theo DPI
    float adjustedFontSize = font_size * (dpiX / 96.0f); // 96 DPI là chuẩn của màn hình

    const WCHAR* fontName = font.c_str();

    // Tạo font với kích thước đã điều chỉnh
    Gdiplus::FontFamily fontFamily(font.c_str());

    float renderX = x + dx;
    float renderY = y + dy;

    Gdiplus::Pen pen(Gdiplus::Color(255, textColor.getRed(), textColor.getGreen(), textColor.getBlue()), stroke_width);
    Gdiplus::SolidBrush brush(Gdiplus::Color(255, textColor.getRed(), textColor.getGreen(), textColor.getBlue()));

    std::wstring textContent(content.begin(), content.end());

    //// Measure the size of the text
    //Gdiplus::RectF textBox;
    //graphics.MeasureString(
    //    textContent.c_str(), // Convert std::string to std::wstring
    //    -1,  // Length of the string (use -1 for null-terminated string)
    //    &font,  // Font object
    //    Gdiplus::PointF(renderX, renderY), // Position of the text
    //    &textBox  // This will store the bounding box for the text
    //);

    //// Adjust the y position based on the text's height
    //float adjustedY = renderY - textBox.Height;  // Adjust to ensure text is positioned correctly

    //PointSVG center = getCenter();
    //transform.apply(graphics, center);

    //// Draw the text at the adjusted position
    //graphics.DrawString(
    //    textContent.c_str(), // Convert std::string to std::wstring
    //    -1,  // Length of the string (use -1 for null-terminated string)
    //    &font,  // Font object
    //    Gdiplus::PointF(renderX, adjustedY), // Use the adjusted y position
    //    &brush  // Brush object for color
    //);

    Gdiplus::GraphicsPath path;
    path.AddString(
        textContent.c_str(),     // Chuỗi ký tự
        -1,                      // Độ dài chuỗi (-1 cho null-terminated string)
        &fontFamily,             // FontFamily
        Gdiplus::FontStyleRegular, // Kiểu font
        adjustedFontSize,        // Kích thước font
        Gdiplus::PointF(renderX, renderY), // Vị trí
        nullptr                  // Định dạng chuỗi
    );

    std::cout << "Text transform: " << transform << std::endl;
    std::cout << "Content: " << content << std::endl;
    std::cout << "Font size: " << font_size << std::endl;
    std::cout << "Fill: " << fill << std::endl;

    // Áp dụng transform
    PointSVG center = getCenter();
    transform.apply(graphics, center);

    // Vẽ stroke trước
    graphics.DrawPath(&pen, &path);

    // Vẽ fill sau
    graphics.FillPath(&brush, &path);
}

PointSVG TextSVG::getCenter() const {
    Gdiplus::Bitmap tempBitmap(1, 1);
    Gdiplus::Graphics graphics(&tempBitmap);

    // Lấy DPI của màn hình
    float dpiX = graphics.GetDpiX();
    float dpiY = graphics.GetDpiY();

    // Điều chỉnh kích thước font theo DPI
    float adjustedFontSize = font_size * (dpiX / 96.0f); // 96 DPI là chuẩn của màn hình

    const WCHAR* fontName = font.c_str();
    
    Gdiplus::Font font(fontName, adjustedFontSize);

    std::wstring textContent(content.begin(), content.end());
    
    float renderX = x + dx;
    float renderY = y + dy;

    Gdiplus::RectF textBox;
    graphics.MeasureString(
        textContent.c_str(), // Convert std::string to std::wstring
        -1,  // Length of the string (use -1 for null-terminated string)
        &font,  // Font object
        Gdiplus::PointF(renderX, renderY), // Position of the text
        &textBox  // This will store the bounding box for the text
    );

    float centerX = renderX + textBox.Width / 2;
    float centerY = renderY + textBox.Height / 2;

	return PointSVG(centerX, centerY);
}

float TextSVG::getFontSize() const {
	return font_size;
}

void TextSVG::setFontSize(float value) {
	font_size = value;
}

void TextSVG::applyFontSize(float font_size) {
	setFontSize(font_size);
}