#ifndef TEXT_H
#define TEXT_H

#include "SVGElements.h"

class Text : public SVGElements {
private:
    int x, y;
    int font_size;
    std::string content;
    std::string fill;

public:
    Text(int x, int y, int font_size, const std::string& content, const std::string& fill);
    void render() const override;
};

#endif // TEXT_H