#include "Element.h"

// Constructor
// Rect Constructor
Rect::Rect(int x, int y, int width, int height, const std::string& fill, const std::string& stroke)
    : x(x), y(y), width(width), height(height), fill(fill), stroke(stroke) {}

// Circle Constructor
Circle::Circle(int cx, int cy, int r, const std::string& fill)
    : cx(cx), cy(cy), r(r), fill(fill) {}

// Line Constructor
Line::Line(int x1, int y1, int x2, int y2, const std::string& stroke)
    : x1(x1), y1(y1), x2(x2), y2(y2), stroke(stroke) {}

// Path Constructor
Path::Path(const std::vector<std::pair<int, int> >& points, const std::string& stroke)
    : points(points), stroke(stroke) {}

// Text Constructor
Text::Text(int x, int y, const std::string& content, const std::string& fill, const std::string& stroke)
    : x(x), y(y), content(content), fill(fill), stroke(stroke) {}

// Ellipse Constructor
Ellipse::Ellipse(int cx, int cy, int rx, int ry, const std::string& fill, const std::string& stroke)
    : cx(cx), cy(cy), rx(rx), ry(ry), fill(fill), stroke(stroke) {}

// Polygon Constructor
Polygon::Polygon(const std::vector<std::pair<int, int> >& points, const std::string& stroke, const std::string& fill)
    : points(points), stroke(stroke), fill(fill) {}

// Destructor
// Rect Destructor
Rect::~Rect() {
    delete this;
}

// Circle Destructor
Circle::~Circle() {
	delete this;
}

// Line Destructor
Line::~Line() {
	delete this;
}

// Path Destructor 
Path::~Path() {
	delete this;
}

// Text Destructor
Text::~Text() {
	delete this;
}

// Ellipse Destructor
Ellipse::~Ellipse() {
	delete this;
}

// Polygon Destructor
Polygon::~Polygon() {
	delete this;
}

// Render functions
void Rect::render() const
{
    std::cout << "Rendering Rectangle: x = " << x << ", y = " << y
              << ", width = " << width << ", height = " << height
              << ", fill = " << fill << ", stroke = " << stroke << std::endl;
}

void Circle::render() const
{
    std::cout << "Rendering Circle: cx = " << cx << ", cy = " << cy
              << ", radius = " << r << ", fill = " << fill << std::endl;
}

void Line::render() const
{
    std::cout << "Rendering Line: (" << x1 << ", " << y1 << ") to ("
              << x2 << ", " << y2 << "), stroke = " << stroke << std::endl;
}

void Path::render() const
{
    std::cout << "Rendering Path with points: ";
    for (const auto& point : points)
    {
        std::cout << "(" << point.first << ", " << point.second << ") ";
    }
    std::cout << ", stroke = " << stroke << std::endl;
}

void Text::render() const
{
    std::cout << "Rendering Text: \"" << content << "\" at (" << x << ", " << y
              << "), fill = " << fill << ", stroke = " << stroke << std::endl;
}

void Ellipse::render() const
{
    std::cout << "Rendering Ellipse: cx = " << cx << ", cy = " << cy
              << ", rx = " << rx << ", ry = " << ry << ", fill = " << fill
              << ", stroke = " << stroke << std::endl;
}

void Polygon::render() const
{
    std::cout << "Rendering Polygon with points: ";
    for (const auto& point : points)
    {
        std::cout << "(" << point.first << ", " << point.second << ") ";
    }
    std::cout << ", stroke = " << stroke << ", fill = " << fill << std::endl;
}

// SVGDocuments methods
void SVGDocuments::addElement(SVGElements* element)
{
    if (element != nullptr) {
        elements.push_back(element);
    }

    else {
        cout << "Error: Element is null" << endl;
    }
}

void SVGDocuments::modifyElement(int elementId, SVGElements* newElement)
{
    if (elementId >= 0 && elementId < elements.size())
    {
        delete elements[elementId];
        elements[elementId] = newElement;
    }
}

void SVGDocuments::removeElement(int elementId)
{
    if (elementId >= 0 && elementId < elements.size())
    {
        delete elements[elementId];
        elements.erase(elements.begin() + elementId);
    }
}

std::vector<SVGElements*>& SVGDocuments::getElements() 
{
    return elements;  // Trả về tham chiếu đến vector
}

SVGDocuments::~SVGDocuments()
{
    elements.clear();
}
