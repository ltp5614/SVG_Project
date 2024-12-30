#ifndef POINT_H
#define POINT_H

class PointSVG {
private:
    float x;
    float y;

public:
    PointSVG();
    PointSVG(float x, float y);

    float getX();
    float getY();
    void setX(float);
    void setY(float);
};

#endif
