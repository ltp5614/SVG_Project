#ifndef PATH_H
#define PATH_H

#include "SVGElements.h"

class Path : public SVGElements {
private:
    std::vector<std::pair<int, int>> points;
    std::string fill;
    std::string stroke;
    double fill_opacity;
    int stroke_width;
    double stroke_opacity;

public:
    Path(const std::vector<std::pair<int, int>>& points, const std::string& fill, double fill_opacity, const std::string& stroke, int stroke_width, double stroke_opacity);
    void render() const override;
};

std::vector<std::pair<int, int>> parsePathData(const std::string& d);

#endif // PATH_H
