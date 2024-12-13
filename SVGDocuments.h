#ifndef SVGDOCUMENTS_H
#define SVGDOCUMENTS_H

#include "SVGElements.h"
#include "Rect.h"
#include "Circle.h"
#include "Line.h"
#include "Path.h"
#include "Text.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "Polyline.h"
#include "rapidxml.hpp"

#include <fstream>

using namespace rapidxml;

class SVGDocuments {
private:
    std::vector<std::unique_ptr<SVGElements>> elements;

public:
    SVGDocuments loadFile(const std::string& filePath);
    void addElement(std::unique_ptr<SVGElements> element);
    void modifyElement(int elementId, std::unique_ptr<SVGElements> newElement);
    void removeElement(int elementId);
    std::vector<std::unique_ptr<SVGElements>>& getElements();
    void render() const;
};

std::vector<std::pair<int, int>> parsePoints(const std::string& pointsStr);

#endif // SVGDOCUMENTS_H