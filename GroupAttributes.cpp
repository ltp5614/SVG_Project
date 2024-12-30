#include "GroupAttributes.h"

GroupAttributes::GroupAttributes() : fill("none"), fillOpacity(1.0f), 
									 stroke("none"), strokeWidth(0.0f), strokeOpacity(1.0f),
									 transform(), fontSize(0.0f) {}

GroupAttributes::GroupAttributes(const std::string& fill, float fillOpacity,
								 const std::string& stroke, float strokeWidth,
								 float strokeOpacity, Transform& transform,
								 float fontSize)
	: fill(fill), fillOpacity(fillOpacity), 
	  stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity), 
	  transform(transform), 
	  fontSize(fontSize) {}

void GroupAttributes::applyAttributesToChild(SVGElements& element) const {
	element.applyAttributes(fill, fillOpacity, stroke, strokeWidth, strokeOpacity, transform);

	if (auto text = dynamic_cast<TextSVG*>(&element)) {
		text->applyFontSize(fontSize);
	}
}

void GroupAttributes::setFill(const std::string& fill) { this->fill = fill; }
void GroupAttributes::setFillOpacity(float fillOpacity) { this->fillOpacity = fillOpacity; }
void GroupAttributes::setStroke(const std::string& stroke) { this->stroke = stroke; }
void GroupAttributes::setStrokeWidth(float strokeWidth) { this->strokeWidth = strokeWidth; }
void GroupAttributes::setStrokeOpacity(float strokeOpacity) { this->strokeOpacity = strokeOpacity; }
void GroupAttributes::setTransform(const Transform& transform) { this->transform = transform; }
void GroupAttributes::setFontSize(float fontSize) { this->fontSize = fontSize; }

const std::string& GroupAttributes::getFill() { return fill; }
float GroupAttributes::getFillOpacity() const { return fillOpacity; }
const std::string& GroupAttributes::getStroke() { return stroke; }
float GroupAttributes::getStrokeWidth() const { return strokeWidth; }
float GroupAttributes::getStrokeOpacity() const { return strokeOpacity; }
const Transform& GroupAttributes::getTransform() { return transform; }
float GroupAttributes::getFontSize() const { return fontSize; }