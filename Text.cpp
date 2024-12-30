#include "Text.h"

TextSVG::TextSVG(float x, float y, float dx, float dy,
                 float font_size, const std::string& content, const std::wstring& font,
<<<<<<< HEAD
                 const std::string& text_anchor, const std::string& font_style,
=======
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
                 const std::string& fill, float fill_opacity, 
                 const std::string& stroke, float stroke_width, float stroke_opacity,
                 Transform transform)
        : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform),
<<<<<<< HEAD
          x(x), y(y), dx(dx), dy(dy), font_size(font_size), content(content), font(font), text_anchor(text_anchor), font_style(font_style) {}

std::wstring TextSVG::trimQuotes(const std::wstring& str) const
{
    if (!str.empty() && 
        ((str.front() == L'"' && str.back() == L'"') || 
         (str.front() == L'\'' && str.back() == L'\''))) {
        return str.substr(1, str.size() - 2);
    }
    return str;
}

// Hàm tách các font từ chuỗi font-family
std::vector<std::wstring> TextSVG::parseFontFamily(const std::wstring& fontFamily) const
{
    std::cout << "+++++" << stroke_width << std::endl;
    std::vector<std::wstring> fonts;
    std::wstringstream ss(fontFamily);
    std::wstring font;

    // Tách bằng dấu phẩy
    while (std::getline(ss, font, L',')) {
        // Loại bỏ khoảng trắng thừa
        font.erase(0, font.find_first_not_of(L" \t\n\r"));
        font.erase(font.find_last_not_of(L" \t\n\r") + 1);
        // Loại bỏ dấu ngoặc kép nếu có
        if (!font.empty()) {
            fonts.push_back(trimQuotes(font));
        }
    }
    return fonts;
}
void TextSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const
{
    std::cout << x << " " << y << " " << dx << " " << dy << std::endl;

    // Convert the fill color string into a Color object
    ColorSVG textColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(fill);
    ColorSVG strokeColor = (fill == "none" && stroke == "none") ? ColorSVG(0, 0, 0) : ColorSVG::parseColor(stroke);

    // Khởi tạo đối tượng Graphics
    Gdiplus::Matrix currentMatrix;
    Gdiplus::REAL Elements[6];
    matrix.GetElements(Elements);
    currentMatrix.SetElements(Elements[0], Elements[1], Elements[2], Elements[3], Elements[4], Elements[5]);

    // Chuyển đổi font name từ std::string sang std::wstring
    const std::wstring wfontName(font.begin(), font.end());
    
    // Phân tích danh sách font-family
    std::vector<std::wstring> fontList = parseFontFamily(wfontName);

    // Tìm font hợp lệ đầu tiên trong danh sách
    Gdiplus::Font* selectedFont = nullptr;
    for (const auto& fontName : fontList) {
        Gdiplus::Font testFont(fontName.c_str(), font_size);
        if (testFont.GetLastStatus() == Gdiplus::Ok) {
            selectedFont = new Gdiplus::Font(fontName.c_str(), font_size);
            break;
        }
    }

    // Nếu không tìm thấy font hợp lệ, dùng một font mặc định
    if (!selectedFont) {
        selectedFont = new Gdiplus::Font(L"Arial", font_size); // Arial là font mặc định
    }

    // Lấy vị trí ban đầu của văn bản
    float renderX = x + dx;
    float renderY = y + dy;

    // Hàm để giới hạn giá trị (clamp)
    auto clamp = [](int value, int min, int max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    };
    
    int textAlpha = (fill == "none" && stroke == "none") ? 255 : static_cast<int>(255 * fill_opacity);
    int strokeAlpha = (fill == "none" && stroke == "none") ? 255 : static_cast<int>(255 * stroke_opacity);

    // Tạo SolidBrush cho fill
    Gdiplus::SolidBrush fillBrush(
        Gdiplus::Color(
            static_cast<BYTE>(clamp(textAlpha, 0, 255)),
            static_cast<BYTE>(clamp(textColor.getRed(), 0, 255)),
            static_cast<BYTE>(clamp(textColor.getGreen(), 0, 255)),
            static_cast<BYTE>(clamp(textColor.getBlue(), 0, 255))
        )
    );

    // Tạo Pen cho stroke
    Gdiplus::Pen strokePen(
        Gdiplus::Color(
            static_cast<BYTE>(clamp(strokeAlpha, 0, 255)),
            static_cast<BYTE>(clamp(strokeColor.getRed(), 0, 255)),
            static_cast<BYTE>(clamp(strokeColor.getGreen(), 0, 255)),
            static_cast<BYTE>(clamp(strokeColor.getBlue(), 0, 255))
        ),
        stroke_width
    );

    std::wstring textContent(content.begin(), content.end());

    Gdiplus::RectF bounds;
    graphics.MeasureString(textContent.c_str(), -1, selectedFont, Gdiplus::PointF(0, 0), &bounds);


    // Căn lề
    float adjustedRenderX = renderX;
    float adjustedRenderY = renderY - bounds.Height / 2 - 1;

    // Tạo GraphicsPath để chứa văn bản
    Gdiplus::GraphicsPath path;

    // Lấy FontFamily từ Font
    Gdiplus::FontFamily fontFamily;
    selectedFont->GetFamily(&fontFamily);

    // Xử lý font-style (italic, normal, oblique)
    Gdiplus::FontStyle fontStyle = Gdiplus::FontStyleRegular;
    if (font_style == "italic") {
        fontStyle = Gdiplus::FontStyleItalic;  // Sử dụng FontStyleItalic thay cho FontStyleOblique
    } else if (font_style == "oblique") {
        fontStyle = Gdiplus::FontStyleItalic;  // Oblique cũng được mô phỏng bằng FontStyleItalic
    }

    // Tạo đối tượng StringFormat (có thể dùng nullptr nếu không có yêu cầu định dạng đặc biệt)
    Gdiplus::StringFormat* stringFormat = new Gdiplus::StringFormat();
    
    // Xử lý text-anchor
    if (text_anchor == "middle") {
        stringFormat->SetAlignment(Gdiplus::StringAlignmentCenter);  // Căn giữa
    } else if (text_anchor == "end") {
        stringFormat->SetAlignment(Gdiplus::StringAlignmentFar);  // Căn phải
    } else {
        stringFormat->SetAlignment(Gdiplus::StringAlignmentNear);  // Căn trái (mặc định)
    }

    stringFormat->SetLineAlignment(Gdiplus::StringAlignmentNear);  // Căn lên
    stringFormat->SetHotkeyPrefix(Gdiplus::HotkeyPrefixNone);  // Tắt hotkey
    stringFormat->SetTrimming(Gdiplus::StringTrimmingNone);  // Không cắt bớt văn bản

    // Thêm chuỗi vào GraphicsPath
    path.AddString(
        textContent.c_str(),
        -1,  // Độ dài của chuỗi
        &fontFamily,
        fontStyle,
        font_size,
        Gdiplus::PointF(adjustedRenderX, adjustedRenderY),
        stringFormat
    );

    // Áp dụng transform sau khi tính toán vị trí
    PointSVG center = getCenter();
    transform.apply(currentMatrix, center);
    graphics.SetTransform(&currentMatrix);

    // Vẽ stroke (viền) cho văn bản
    graphics.DrawPath(&strokePen, &path);

    // Vẽ phần fill của văn bản
    graphics.FillPath(&fillBrush, &path);
}





=======
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

>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
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
<<<<<<< HEAD
}
=======
}
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
