#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class SVGElements 
{
public:
    virtual void render() const = 0;
    virtual ~SVGElements() = default;
};

class SVGDocuments
{
private:
    std::vector<SVGElements*> elements;

public:
    void addElement(SVGElements* element);
    void modifyElement(int elementId, SVGElements* newElement);
    void removeElement(int elementId);
    std::vector<SVGElements*>& getElements();
    ~SVGDocuments();
};

class Rect : public SVGElements 
{
   private:
      int x, y, width, height;
      std::string fill;
      std::string stroke;

   public:
      Rect(int x, int y, int width, int height, const std::string& fill, const std::string& stroke);
      void render() const override;
      ~Rect();
};

class Circle : public SVGElements
{
private:
    int cx, cy, r;
    std::string fill;

public:
    Circle(int cx, int cy, int r, const std::string& fill);
    void render() const override;
    ~Circle();
};

class Line : public SVGElements
{
private:
    int x1, y1, x2, y2;
    std::string stroke;

public:
    Line(int x1, int y1, int x2, int y2, const std::string& stroke);
    void render() const override;
    ~Line();
};

class Path : public SVGElements
{
private:
    std::vector<std::pair<int, int> > points;
    std::string stroke;

public:
    Path(const std::vector<std::pair<int, int> >& points, const std::string& stroke);
    void render() const override;
    ~Path();
};

class Text : public SVGElements
{
private:
    int x, y;
    std::string content;
    std::string fill;
    std::string stroke;

public:
    Text(int x, int y, const std::string& content, const std::string& fill, const std::string& stroke);
    void render() const override;
    ~Text();
};

class Ellipse : public SVGElements
{
private:
    int cx, cy;
    int rx, ry;
    std::string fill;
    std::string stroke;

public:
    Ellipse(int cx, int cy, int rx, int ry, const std::string& fill, const std::string& stroke);
    void render() const override;
    ~Ellipse();
};

class Polygon : public SVGElements
{
private:
    std::vector<std::pair<int, int>> points;
    std::string stroke;
    std::string fill;

public:
    Polygon(const std::vector<std::pair<int, int> >& points, const std::string& stroke, const std::string& fill);
    void render() const override;
    ~Polygon();
};
