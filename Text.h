#ifndef TEXT_H
#define TEXT_H

#include "SVGElements.h"
#include <iostream>

class TextSVG : public SVGElements {
private:
    float x, y;
    float dx, dy;
    float font_size;
    std::string content;
    std::wstring font;
<<<<<<< HEAD
    std::string text_anchor;
    std::string font_style;

public:
    TextSVG(float x, float y, float dx, float dy,
            float font_size, const std::string& content, const std::wstring& font, const std::string& text_anchor, const std::string& font_style,
=======

public:
    TextSVG(float x, float y, float dx, float dy,
            float font_size, const std::string& content, const std::wstring& font,
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
            const std::string& fill, float fill_opacity, 
            const std::string& stroke, float stroke_width, float stroke_opacity,
            Transform transform);

<<<<<<< HEAD
    void render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const override;
    PointSVG getCenter() const override;
    std::wstring trimQuotes(const std::wstring& str) const;
    std::vector<std::wstring> parseFontFamily(const std::wstring& fontFamily) const;

    // Getter vï¿½ Setter
=======
    void render(HDC hdc) const override;
    PointSVG getCenter() const override;

    // Getter và Setter
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
    float getFontSize() const;
    void setFontSize(float value);

    void applyFontSize(float font_size);
};

#endif // TEXT_H
