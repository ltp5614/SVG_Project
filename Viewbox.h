#ifndef VIEWBOX_H
#define VIEWBOX_H

#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <gdiplus.h>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;
using namespace Gdiplus;

#pragma comment(lib, "Gdiplus.lib")

const float DefaultScale = 1.0f;

class Viewbox {
private:
    float viewX, viewY, viewWidth, viewHeight;
    float portWidth, portHeight;
    std::string preservedForm, preservedMode;

public:
	// Constructor
	Viewbox();
	Viewbox(float viewX, float viewY, float viewWidth, float viewHeight, 
			float portWidth, float portHeight, 
			const std::string& preservedForm, const std::string& preservedMode);

	// Getter
	float getViewX() const;
	float getViewY() const;
	float getViewWidth() const;
	float getViewHeight() const;
	float getPortWidth() const;
	float getPortHeight() const;
	std::string getPreservedForm() const;
	std::string getPreservedMode() const;

	void parseViewbox(rapidxml::xml_node<>* node);
	void render(Graphics& graphics, RECT& window);
};

#endif // VIEWBOX_H
