//Group.cpp

#include "Group.h"
#include "Text.h"
<<<<<<< HEAD
#include "Circle.h"

//Constructor
GroupSVG::GroupSVG(std::vector<std::unique_ptr<SVGElements>> elements, const std::string& fill, float fill_opacity, 
               const std::string& stroke, float stroke_width, float stroke_opacity,
               Transform transform, float fontSize)
		 : SVGElements(fill, stroke, fill_opacity, stroke_width, stroke_opacity, transform),
           elements(std::move(elements)), fontSize(fontSize) 
{
                // Bỏ qua mọi điều kiện, áp dụng trực tiếp giá trị
    this->fill = fill;
    this->stroke = stroke;
    this->fill_opacity = fill_opacity;
    this->stroke_width = stroke_width;
    this->stroke_opacity = stroke_opacity;
    this->transform = transform;
    this->fontSize = fontSize;

}

void GroupSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& parentMatrix) const {
    Gdiplus::Matrix currentMatrix;

    Gdiplus::REAL Elements[6];
    parentMatrix.GetElements(Elements);

    // Tạo một bản sao của ma trận từ cha
    currentMatrix.SetElements(Elements[0], Elements[1],
                          Elements[2], Elements[3],
                          Elements[4], Elements[5]);



    // Áp dụng phép biến đổi của nhóm hiện tại
    PointSVG center = getCenter();
    transform.apply(currentMatrix, center);

    graphics.SetTransform(&currentMatrix);
    Gdiplus::GraphicsState state = graphics.Save();

    for (const auto& element : elements) {
        if (auto groupElement = dynamic_cast<GroupSVG*>(element.get())) {

            groupElement->render(graphics, currentMatrix);
        } else {

            element->render(graphics, currentMatrix);
        }
    }

    // Phục hồi trạng thái ban đầu của Graphics
    graphics.Restore(state);
}



=======

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

>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
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

<<<<<<< HEAD
void GroupSVG::applyGroupAttributes() 
{
    // Áp dụng thuộc tính của nhóm cho các phần tử trong nhóm
    for (const auto& element : elements) {
        // Áp dụng thuộc tính cho phần tử
        element->applyAttributes(this->fill,
                                 this->fill_opacity, 
                                 this->stroke,
                                 this->stroke_width,
                                 this->stroke_opacity, 
                                 this->transform);

        // Kiểm tra nếu phần tử là TextSVG
        if (auto textElement = dynamic_cast<TextSVG*>(element.get())) {
            if (textElement->getFontSize() == 0.0f) {
                textElement->setFontSize(this->fontSize);
            }
        }

        // Kiểm tra nếu phần tử là GroupSVG
        if (auto groupElement = dynamic_cast<GroupSVG*>(element.get())) {
            // Gọi đệ quy để áp dụng thuộc tính cho các phần tử trong nhóm con
            groupElement->applyGroupAttributes();
        }
    }
}


void GroupSVG::inheritedAttributes(const std::string& fill, float fill_opacity, 
               const std::string& stroke, float stroke_width, float stroke_opacity,
               Transform transform, float fontSize)
{
    // Chỉ áp dụng nếu giá trị khác "none" hoặc > 0
    if (this->fill == "none") {
        this->fill = fill;
    }
    if (this->fill_opacity == 1.0f && fill_opacity != 0) { // Chỉ áp dụng nếu độ trong suốt khác 1.0 (mặc định đầy đủ)
        this->fill_opacity = fill_opacity;
    }
    if (this->stroke == "none") {
        this->stroke = stroke;
    }
    if (this->stroke_width == 0.0f) {
        this->stroke_width = stroke_width;
    }
    if (this->stroke_opacity == 1.0f &&  stroke_opacity != 0) {
        this->stroke_opacity = stroke_width;
    }

    // Chỉ áp dụng kích thước phông nếu lớn hơn 0
    if (fontSize == 0.0f) {
        this->fontSize = fontSize;
    }
}


=======
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
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
