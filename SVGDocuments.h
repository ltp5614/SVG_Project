#ifndef SVGDOCUMENTS_H
#define SVGDOCUMENTS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include "SVGElements.h"
<<<<<<< HEAD
#include "Viewbox.h"
=======

class SVGElementsFactory;
class SVGFactoryRegistry;
class SVGFactoryRegistrar;
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f

class SVGDocuments {
private:
    std::vector<std::unique_ptr<SVGElements>> elements;

public:
<<<<<<< HEAD
    SVGDocuments loadFile(const std::string& filePath, Viewbox* viewbox);
=======
    SVGDocuments loadFile(const std::string& filePath);
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
    void addElement(std::unique_ptr<SVGElements> element);
    void modifyElement(int elementId, std::unique_ptr<SVGElements> newElement);
    void removeElement(int elementId);
    std::vector<std::unique_ptr<SVGElements>>& getElements();
<<<<<<< HEAD
    void render(Graphics& graphics) const;
};

std::vector<std::pair<float, float>> parsePoints(const std::string& pointsStr);
=======
    void render(HDC hdc) const;
};

std::vector<std::pair<int, int>> parsePoints(const std::string& pointsStr);
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f

#endif // SVGDOCUMENTS_H
