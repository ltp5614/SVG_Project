//Group.cpp

#include "Group.h"
#include "Text.h"

//Constructor
GroupSVG::GroupSVG(std::vector<std::unique_ptr<SVGElements>> elements, GroupAttributes attributes)
		 : SVGElements(attributes.getFill(), attributes.getStroke(), 
                       attributes.getFillOpacity(), 
                       attributes.getStrokeWidth(), attributes.getStrokeOpacity(), 
                       attributes.getTransform()),
           elements(std::move(elements)), attributes(attributes) {}

void GroupSVG::render(HDC hdc) const {
    Gdiplus::Graphics graphics(hdc);

    // Lặp qua các phần tử trong nhóm
    for (const auto& element : elements) {
        Gdiplus::GraphicsState state = graphics.Save();

        Gdiplus::Matrix currentTransform;
        graphics.GetTransform(&currentTransform);

        // Áp dụng transform của group
        Gdiplus::Matrix groupTransform;
        PointSVG center = getCenter();
        transform.apply(graphics, center); // Áp dụng transform riêng của nhóm
        currentTransform.Multiply(&groupTransform, Gdiplus::MatrixOrderPrepend);

        // Thiết lập transform cho graphics
        graphics.SetTransform(&currentTransform);

        // Kiểm tra nếu phần tử là nhóm con (có thể có fill, stroke riêng)
        if (auto groupElement = dynamic_cast<GroupSVG*>(element.get())) {
           
            groupElement->render(hdc);
        }

        // Nếu không phải nhóm con, render bình thường
        else {
            element->render(hdc);
        }

        graphics.Restore(state);
    }
}

// Phương thức tính toán tâm của nhóm (center of group)
PointSVG GroupSVG::getCenter() const {
    float sumX = 0, sumY = 0;
    size_t count = 0;

    for (const auto& element : elements) {
        PointSVG elementCenter = element->getCenter();
 
        sumX += elementCenter.getX();
        sumY += elementCenter.getY();

        count++;
    }

    // Trả về trung tâm của nhóm
    return PointSVG(sumX / count, sumY / count);
}

void GroupSVG::applyGroupAttributes(const std::string& groupFill, float groupFillOpacity,
									const std::string& groupStroke, float groupStrokeWidth,
									float groupStrokeOpacity, const Transform& groupTransform,
									float groupFontSize) {
    std::cout << "Applying group attributes"
              << "G Fill: " << groupFill
        << "G Fill Opacity: " << groupFillOpacity
        << "G Stroke: " << groupStroke
        << "G Stroke Width: " << groupStrokeWidth
        << "G Stroke Opacity: " << groupStrokeOpacity
        << "G Transform: " << groupTransform
        << "G Font Size: " << groupFontSize << std::endl;

	// Áp dụng thuộc tính của nhóm cho các phần tử trong nhóm
	for (const auto& element : elements) {
        element->applyAttributes(groupFill, groupFillOpacity, groupStroke, groupStrokeWidth, groupStrokeOpacity, groupTransform);

        if (auto textElement = dynamic_cast<TextSVG*>(element.get())) {
            std::cout << "Found text element" << std::endl;
            
			// Áp dụng font size
			if (textElement->getFontSize() == 0.0f) {
				textElement->setFontSize(groupFontSize);
			}

            std::cout << "After applyGroupAttributes: "
				<< "Font Size: " << textElement->getFontSize() << std::endl;
		}
	}
}