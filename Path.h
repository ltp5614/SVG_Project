#ifndef PATH_H
#define PATH_H

#include "SVGElements.h"
#include "PathCommand.h"

class PathSVG : public SVGElements{
private:
    std::vector<PathCommand> commands;

<<<<<<< HEAD
    void skipWhitespace(const std::string& str, int& index) const;
    // Hàm đọc một số (float)
    float parseNumber(const std::string& str, int& index) const;


=======
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
public:
    PathSVG(const std::string& pointsData, 
            const std::string& fill, float fill_opacity,
            const std::string& stroke, float stroke_width, float stroke_opacity,
            Transform transform);

<<<<<<< HEAD
=======
    void skipWhitespace(const std::string& str, int& index) const;
    // Hàm đọc một số (float)
    float parseNumber(const std::string& str, int& index) const;

>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
    void renderArc(Gdiplus::Graphics& graphics, Gdiplus::GraphicsPath& path, 
                   Gdiplus::PointF& currentPoint, const std::vector<float>& params) const;

    std::vector<Gdiplus::PointF> calculateBezierForArc(float cx, float cy, float rx, float ry, 
                                                       float xAxisRotation, float thetaStart, float thetaEnd) const;

    void calculateArcParameters(const Gdiplus::PointF& currentPoint, const Gdiplus::PointF& endPoint, 
                                float rx, float ry, float xAxisRotation, int largeArcFlag, int sweepFlag, 
                                float& cx, float& cy, float& theta1, float& deltaTheta) const;

    void addCommand(const PathCommand& command);

    // Lấy danh sách các lệnh
    const std::vector<PathCommand>& getCommands() const;

    // Chuyển toàn bộ path thành chuỗi SVG
    std::string toSVGString() const;

    // Xóa toàn bộ path
    void clear();
<<<<<<< HEAD
    int getNumberOfParametersForCommand(char command) const;

    // Phân tích chuỗi SVG path và nạp vào Path
    void parseFromSVGString(const std::string& svgPath);
    void render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const override;

=======

    // Phân tích chuỗi SVG path và nạp vào Path
    void parseFromSVGString(const std::string& svgPath);
    void render(HDC hdc) const override;
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
    PointSVG getCenter() const override;
};

#endif // PATH_H
