#include "Text.h"

TextSVG::TextSVG(float x, float y, float dx, float dy,
                 float font_size, const std::string& content, const std::wstring& font,
                 const std::string& text_anchor, const std::string& font_style,
                 const std::string& fill, float fill_opacity, 
                 const std::string& stroke, float stroke_width, float stroke_opacity,
                 Transform transform)
        : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform),
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
void TextSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix, GradientManager gradients) const
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


    if (textAlpha == -1) 
      textAlpha = 0;
    
    if (strokeAlpha == -1)
      strokeAlpha = 0;

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
    transform.apply(currentMatrix);
    graphics.SetTransform(&currentMatrix);


    // Chiều rộng và chiều cao của box chứa văn bản
    float textWidth = bounds.Width;
    float textHeight = bounds.Height;


        Gdiplus::Brush* fillBrush = nullptr;
    if (fill.find("url(") == 0) {
        // Lấy ID gradient từ `fill="url(#gradient_id)"`
        std::string gradientId = fill.substr(5, fill.size() - 6); // Bỏ "url(" và ")"
        const Gradient* gradient = gradients.getGradient(gradientId); // Hàm getGradientById bạn tự cài đặt
        
        if (gradient) {
            gradient->applyForBrush(matrix, fillBrush, textWidth, textHeight); // Áp dụng gradient
        }
     
    }

    if (!fillBrush) {
        // Nếu không có gradient, sử dụng màu solid

        ColorSVG textColor = ColorSVG::parseColor(fill);
        fillBrush = new Gdiplus::SolidBrush(
            Gdiplus::Color(
                static_cast<BYTE>(clamp(textAlpha, 0, 255)), // Alpha
                static_cast<BYTE>(clamp(textColor.getRed(), 0, 255)),  // Red
                static_cast<BYTE>(clamp(textColor.getGreen(), 0, 255)),  // Green
                static_cast<BYTE>(clamp(textColor.getBlue(), 0, 255))  // Blue
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

    // Vẽ stroke (viền) cho văn bản
    graphics.DrawPath(strokePen, &path);

    // Vẽ phần fill của văn bản
    graphics.FillPath(fillBrush, &path);
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
