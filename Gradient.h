#ifndef GRADIENT_H
#define GRADIENT_H

#include <string>
#include <windows.h>
#include <gdiplus.h>
#include <algorithm>
#include "rapidxml.hpp"
#include "Color.h"
#include <iostream>

using namespace std;

struct GradientStop {
    float offset;       // Vị trí của điểm dừng (0.0 - 1.0)
    std::string color;  // Màu tại điểm dừng (ví dụ: "#FF0000" cho màu đỏ)
    float opacity;      // Độ trong suốt tại điểm dừng (0.0 - 1.0)
};


class Gradient {
protected:
    std::vector<GradientStop> stops;

public:
    std::vector<GradientStop> getStops();
    virtual void addStop(float offset, const std::string& color, float opacity) = 0;
    virtual void applyForBrush(const Gdiplus::Matrix& matrix, Gdiplus::Brush*& brush, float boundingBoxWidth, float boundingBoxHeight) const = 0;
    virtual ~Gradient() = default;
};

class LinearGradient : public Gradient {
private:
    std::string x1, y1, x2, y2;
public:
    void addStop(float offset, const std::string& color, float opacity);
    LinearGradient(std::string x1, std::string y1, std::string x2, std::string y2);
    void applyForBrush(const Gdiplus::Matrix& matrix, Gdiplus::Brush*& brush, float boundingBoxWidth, float boundingBoxHeight) const override;
};

class RadialGradient : public Gradient {
private:
    std::string x1, y1;
    std::string radius;
public:
    void addStop(float offset, const std::string& color, float opacity);
    RadialGradient(std::string x1, std::string y1, std::string radius);
    void applyForBrush(const Gdiplus::Matrix& matrix, Gdiplus::Brush*& brush, float boundingBoxWidth, float boundingBoxHeight) const override;
    
};

#endif 
