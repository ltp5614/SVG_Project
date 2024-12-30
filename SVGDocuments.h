#ifndef SVGDOCUMENTS_H
#define SVGDOCUMENTS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include "SVGElements.h"
#include "Viewbox.h"

class SVGDocuments {
private:
    std::vector<std::unique_ptr<SVGElements>> elements;

public:
    SVGDocuments loadFile(const std::string& filePath, Viewbox* viewbox);
    void addElement(std::unique_ptr<SVGElements> element);
    void modifyElement(int elementId, std::unique_ptr<SVGElements> newElement);
    void removeElement(int elementId);
    std::vector<std::unique_ptr<SVGElements>>& getElements();
    void render(Graphics& graphics) const;
};

std::vector<std::pair<float, float>> parsePoints(const std::string& pointsStr);

#endif // SVGDOCUMENTS_H
