#ifndef GROUP_H
#define GROUP_H

#include <memory>
#include <vector>
#include "SVGElements.h"
<<<<<<< HEAD
=======
#include "GroupAttributes.h"
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f

class GroupSVG : public SVGElements {
private:
	std::vector<std::unique_ptr<SVGElements>> elements;
<<<<<<< HEAD
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
=======
	GroupAttributes attributes;

public:
	GroupSVG(std::vector<std::unique_ptr<SVGElements>> elements, GroupAttributes groupAttributes);

	void render(HDC hdc) const override;
	PointSVG getCenter() const override;
	void applyGroupAttributes(const std::string& groupFill, float groupFillOpacity,
							  const std::string& groupStroke, float groupStrokeWidth,
							  float groupStrokeOpacity, const Transform& groupTransform,
							  float groupFontSize);
};


#endif // GROUP_H
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
