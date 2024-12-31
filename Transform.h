#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <windows.h>
#include <gdiplus.h>
#include "rapidxml.hpp"
#include "Point.h"

#pragma comment (lib,"Gdiplus.lib")

class Transform {
private:
	float translateX, translateY;
	float scaleX, scaleY;
	float rotationAngle;

public:
	//Constructor
	Transform();
	Transform(float translateX, float translateY, float scaleX, float scaleY, float rotationAngle);

	//Apply transform
	void apply(Gdiplus::Matrix& parentMatrix) const;


	//Load transform from file
	static Transform loadTransform(rapidxml::xml_node<>* node);
	static void parseCommand(const std::string& command, const std::string& values, Transform& transform);


	//Getter
	float getTranslateX() const;
	float getTranslateY() const;
	float getScaleX() const;
	float getScaleY() const;
	float getRotationAngle() const;

	//Setter
	void setTranslateX(float translateX);
	void setTranslateY(float translateY);
	void setScaleX(float scaleX);
	void setScaleY(float scaleY);
	void setRotationAngle(float rotationAngle);

	//Operator
	bool operator==(const Transform& other) const;
	bool isDefault() const;

};

#endif
