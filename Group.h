#ifndef GROUP_H
#define GROUP_H

#include <memory>
#include <vector>
#include "SVGElements.h"
#include "GroupAttributes.h"

class GroupSVG : public SVGElements {
private:
	std::vector<std::unique_ptr<SVGElements>> elements;
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