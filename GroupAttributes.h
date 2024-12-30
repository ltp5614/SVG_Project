#ifndef GROUP_ATTRIBUTE_H
#define GROUP_ATTRIBUTE_H

#include "SVGElements.h"
#include "Text.h"

class GroupAttributes {
private:
    std::string fill;
    float fillOpacity;
    std::string stroke;
    float strokeWidth;
    float strokeOpacity;
    Transform transform;
    float fontSize;

public:
    GroupAttributes();

    GroupAttributes(const std::string& fill, float fillOpacity,
                    const std::string& stroke, float strokeWidth,
                    float strokeOpacity, Transform& transform,
                    float fontSize);

    // Phương thức áp dụng các thuộc tính vào phần tử con
    void applyAttributesToChild(SVGElements& element) const;

    // Getter và Setter
    void setFill(const std::string& fill);
    void setFillOpacity(float fillOpacity);
    void setStroke(const std::string& stroke);
    void setStrokeWidth(float strokeWidth);
    void setStrokeOpacity(float strokeOpacity);
    void setTransform(const Transform& transform);
    void setFontSize(float fontSize);

    const std::string& getFill();
    float getFillOpacity() const;
    const std::string& getStroke();
    float getStrokeWidth() const;
    float getStrokeOpacity() const;
    const Transform& getTransform();
    float getFontSize() const;
};

#endif // GROUP_ATTRIBUTE_H