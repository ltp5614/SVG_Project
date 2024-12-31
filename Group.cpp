//Group.cpp

#include "Group.h"
#include "Text.h"
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

void GroupSVG::render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& parentMatrix, GradientManager gradients) const {
    Gdiplus::Matrix currentMatrix;

    Gdiplus::REAL Elements[6];
    parentMatrix.GetElements(Elements);

    // Tạo một bản sao của ma trận từ cha
    currentMatrix.SetElements(Elements[0], Elements[1],
                          Elements[2], Elements[3],
                          Elements[4], Elements[5]);



    // Áp dụng phép biến đổi của nhóm hiện tại
    transform.apply(currentMatrix);

    graphics.SetTransform(&currentMatrix);
    Gdiplus::GraphicsState state = graphics.Save();

    for (const auto& element : elements) {
        if (auto groupElement = dynamic_cast<GroupSVG*>(element.get())) {

            groupElement->render(graphics, currentMatrix, gradients);
        } else {

            element->render(graphics, currentMatrix, gradients);
        }
    }

    // Phục hồi trạng thái ban đầu của Graphics
    graphics.Restore(state);
}

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


