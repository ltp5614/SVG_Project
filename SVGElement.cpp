#include "SVGElements.h"

SVGElements::SVGElements(const std::string& fill, const std::string& stroke, 
                         float fill_opacity, float stroke_width, float stroke_opacity,
                         Transform transform) 
           : fill(fill), stroke(stroke), 
             fill_opacity(fill_opacity), stroke_width(stroke_width), stroke_opacity(stroke_opacity), 
             transform(transform) { 

    if (fill != "none" && fill_opacity == 0) {
        this->fill_opacity = 1;
    }
    
    if (stroke != "none" && stroke_opacity == 0) {
        this->stroke_opacity = 1;
    }
}

// Getter và Setter
std::string SVGElements::getFill() const { return fill; }
void SVGElements::setFill(const std::string& value) { fill = value; }

float SVGElements::getFillOpacity() const { return fill_opacity; }
void SVGElements::setFillOpacity(float value) { fill_opacity = value; }

std::string SVGElements::getStroke() const { return stroke; }
void SVGElements::setStroke(const std::string& value) { stroke = value; }

float SVGElements::getStrokeWidth() const { return stroke_width; }
void SVGElements::setStrokeWidth(float value) { stroke_width = value; }

float SVGElements::getStrokeOpacity() const { return stroke_opacity; }
void SVGElements::SVGElements::setStrokeOpacity(float value) { stroke_opacity = value; }

Transform SVGElements::getTransform() const { return transform; }
void SVGElements::setTransform(const Transform& value) { transform = value; }

void SVGElements::applyAttributes(const std::string& fill, float fill_opacity,
								  const std::string& stroke, float stroke_width,
								  float stroke_opacity, Transform transform) {
    if (fill == "none") {
		this->setFill(fill);
	}

    if (fill_opacity == 1.0f) {
        this->setFillOpacity(fill_opacity);
    }
    
    if (stroke == "none") {
		this->setStroke(stroke);
	}

    if (stroke_width == 0.0f) {
		this->setStrokeWidth(stroke_width);
	}

    if (stroke_opacity == 1.0f) {
        this->setStrokeOpacity(stroke_opacity);
	}
    
    if (transform == Transform()) {
		this->setTransform(transform);
	}

    std::cout << "After applyGroupAttributes in SVGElement: "
        << "Fill: " << fill
        << ", Stroke: " << stroke
        << ", Stroke Width: " << stroke_width
        << ", Stroke Opacity: " << stroke_opacity
        << ", Transform: " << transform << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SVGElements& svgElements) {
	os << "Fill: " << svgElements.fill << std::endl
	   << "Fill Opacity: " << svgElements.fill_opacity << std::endl
	   << "Stroke: " << svgElements.stroke << std::endl
	   << "Stroke Width: " << svgElements.stroke_width << std::endl
	   << "Stroke Opacity: " << svgElements.stroke_opacity << std::endl
	   << "Transform: " << svgElements.transform << std::endl;

	return os;
}