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

public:
    TextSVG(float x, float y, float dx, float dy,
            float font_size, const std::string& content, const std::wstring& font,
            const std::string& fill, float fill_opacity, 
            const std::string& stroke, float stroke_width, float stroke_opacity,
            Transform transform);

    void render(HDC hdc) const override;
    PointSVG getCenter() const override;

    // Getter và Setter
    float getFontSize() const;
    void setFontSize(float value);

    void applyFontSize(float font_size);
};

#endif // TEXT_H
