#ifndef PATHCOMMAND_H
#define PATHCOMMAND_H

#include "SVGElements.h"
#include "Point.h"
#include <vector>
#include <sstream>

class PathCommand {
private:
    char command;
    std::vector<float> parameters;
    std::vector<PointSVG> points;  // Sử dụng vector chứa các điểm kiểu PointSVG

public:
    // Constructor
    PathCommand(char cmd, const std::vector<float>& params);

    // Getter for command
    char getCommand() const;

    // Getter for parameters
    const std::vector<float>& getParameters() const;

    // Convert the command to a string representation
    std::string tostring() const;

    // Getter and setter for points
    std::vector<PointSVG>& getPoints() { return points; }
    const std::vector<PointSVG>& getPoints() const { return points; }

    // Thêm điểm vào lệnh
    void addPoint(const PointSVG& point) { points.push_back(point); }
};

#endif // PATHCOMMAND_H
