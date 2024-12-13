#ifndef SVGDOCUMENTS_H
#define SVGDOCUMENTS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include "SVGElements.h"

class SVGElementsFactory;
class SVGFactoryRegistry;
class SVGFactoryRegistrar;

class SVGDocuments {
private:
    std::vector<std::unique_ptr<SVGElements>> elements;

public:
    SVGDocuments loadFile(const std::string& filePath);
    void addElement(std::unique_ptr<SVGElements> element);
    void modifyElement(int elementId, std::unique_ptr<SVGElements> newElement);
    void removeElement(int elementId);
    std::vector<std::unique_ptr<SVGElements>>& getElements();
    void render(HDC hdc) const;
};

std::vector<std::pair<int, int>> parsePoints(const std::string& pointsStr);

#endif // SVGDOCUMENTS_H
