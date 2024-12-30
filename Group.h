#ifndef GROUP_H
#define GROUP_H

#include <memory>
#include <vector>
#include "SVGElements.h"

class GroupSVG : public SVGElements {
private:
	std::vector<std::unique_ptr<SVGElements>> elements;
  float fontSize;


public:
	GroupSVG(std::vector<std::unique_ptr<SVGElements>> elements, const std::string& fill, float fill_opacity, 
               const std::string& stroke, float stroke_width, float stroke_opacity,
               Transform transform, float fontSize);

  void render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const override;
	PointSVG getCenter() const override;
	void applyGroupAttributes();
  void inheritedAttributes(const std::string& fill, float fill_opacity, 
               const std::string& stroke, float stroke_width, float stroke_opacity,
               Transform transform, float fontSize);
};


#endif // GROUP_H
