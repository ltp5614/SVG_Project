#include "Viewbox.h"
#include <iostream>

// Constructor
Viewbox::Viewbox(): viewX(0), viewY(0), viewWidth(0), viewHeight(0), portWidth(0), portHeight(0), preservedForm(""), preservedMode("") {}

Viewbox::Viewbox(float viewX, float viewY, float viewWidth, float viewHeight, 
			float portWidth, float portHeight, 
			const std::string& preservedForm, const std::string& preservedMode)
			: viewX(viewX), viewY(viewY), viewWidth(viewWidth), viewHeight(viewHeight),
			portWidth(portWidth), portHeight(portHeight),
			preservedForm(preservedForm), preservedMode(preservedMode) {}

// Getter
float Viewbox::getViewX() const {
	return viewX;
}

float Viewbox::getViewY() const {
	return viewY;
}

float Viewbox::getViewWidth() const {
	return viewWidth;
}

float Viewbox::getViewHeight() const {
	return viewHeight;
}

float Viewbox::getPortWidth() const {
	return portWidth;
}

float Viewbox::getPortHeight() const {
	return portHeight;
}

std::string Viewbox::getPreservedForm() const {
	return preservedForm;
}

std::string Viewbox::getPreservedMode() const {
	return preservedMode;
}

void Viewbox::parseViewbox(rapidxml::xml_node<>* node) {
	for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
		std::string attrName = attr->name();
		std::string attrValue = attr->value();

		if (attrName == "viewBox") {
			std::stringstream ss(attrValue);
			std::string token;
			std::vector<float> values;

			while (std::getline(ss, token, ' ')) {
				values.push_back(std::stof(token));
			}

			if (values.size() == 4) {
				viewX = values[0];
				viewY = values[1];
				viewWidth = values[2];
				viewHeight = values[3];
			}
		}

		else if (attrName == "preserveAspectRatio") {
			std::stringstream ss(attrValue);
			std::string token;
			std::vector<std::string> values;

			while (std::getline(ss, token, ' ')) {
				values.push_back(token);
			}

			if (values.size() == 1) {
				preservedForm = values[0];
			}

			else if (values.size() == 2) {
				preservedForm = values[0];
				preservedMode = values[1];
			}
		}

		else if (attrName == "width") {
			portWidth = std::stof(attrValue);
		}

		else if (attrName == "height") {
			portHeight = std::stof(attrValue);
		}
	}
}

void Viewbox::render(Graphics& graphics, RECT& window) {
	float width = 0, height = 0;
	float scaleX = 1, scaleY = 1, scaleXY = 1;

	if (portWidth == 0 || portHeight == 0) {
		width = window.right - window.left - 16;
		height = window.bottom - window.top - 39;
	}

	else {
		width = portWidth;
		height = portHeight;
	}

	scaleX = width / viewWidth;
	scaleY = height / viewHeight;
	scaleXY = min(scaleX, scaleY);

	if (viewHeight != 0 || viewWidth != 0) {
		graphics.SetClip(Gdiplus::RectF(0, 0, width, height));
	}
		
	graphics.ScaleTransform(scaleXY, scaleXY);
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
	graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);
}