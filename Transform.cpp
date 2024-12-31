#include "Transform.h"

//Constructor
Transform::Transform() : translateX(0), translateY(0), scaleX(1), scaleY(1), rotationAngle(0) {}

Transform::Transform(float translateX, float translateY, float scaleX, float scaleY, float rotationAngle)
	: translateX(translateX), translateY(translateY), scaleX(scaleX), scaleY(scaleY), rotationAngle(rotationAngle) {}

void Transform::apply(Gdiplus::Matrix& parentMatrix) const {
	Gdiplus::Matrix matrix;

	matrix.Translate(translateX, translateY);
	matrix.Rotate(rotationAngle);
	matrix.Scale(scaleX, scaleY);

	// Áp dụng phép biến đổi cho ma trận cha
	parentMatrix.Multiply(&matrix);
}

Transform Transform::loadTransform(rapidxml::xml_node<>* node) {
	Transform transform;
	rapidxml::xml_attribute<>* transformAttr = node->first_attribute("transform");

	if (transformAttr) {
		std::string transformStr = transformAttr->value();
		std::regex regex("(\\w+)\\s*\\(([^)]+)\\)");
		std::smatch match;

		while (std::regex_search(transformStr, match, regex)) {
			std::string command = match[1].str();
			std::string values = match[2].str();
			parseCommand(command, values, transform);
			transformStr = match.suffix().str();
		}
	}

	return transform;
}

void Transform::parseCommand(const std::string& command, const std::string& values, Transform& transform) {
	if (command == "translate") {
		float translateX = 0.0f, translateY = 0.0f;
		std::stringstream ss(values);
		ss >> translateX;
		ss.ignore();
		if (!(ss >> translateY)) translateY = 0.0f;
		transform.setTranslateX(translateX);
		transform.setTranslateY(translateY);
	}

	else if (command == "scale") {
		float scaleX = 1.0f, scaleY = 1.0f;
		std::stringstream ss(values);
		ss >> scaleX;
		ss.ignore();
		if (!(ss >> scaleY)) scaleY = scaleX;
		transform.setScaleX(scaleX);
		transform.setScaleY(scaleY);
	}

	else if (command == "rotate") {
		float angle = 0.0f, cx = 0.0f, cy = 0.0f;
		std::stringstream ss(values);
		ss >> angle;

		if (ss >> cx >> cy) {
			// Có thể lưu cx, cy nếu cần
		}
		transform.setRotationAngle(angle);
	}
}


//Getter
float Transform::getTranslateX() const {
	return translateX;
}

float Transform::getTranslateY() const {
	return translateY;
}

float Transform::getScaleX() const {
	return scaleX;
}

float Transform::getScaleY() const {
	return scaleY;
}

float Transform::getRotationAngle() const {
	return rotationAngle;
}

//Setter
void Transform::setTranslateX(float translateX) {
	this->translateX = translateX;
}

void Transform::setTranslateY(float translateY) {
	this->translateY = translateY;
}

void Transform::setScaleX(float scaleX) {
	this->scaleX = scaleX;
}

void Transform::setScaleY(float scaleY) {
	this->scaleY = scaleY;
}

void Transform::setRotationAngle(float rotationAngle) {
	this->rotationAngle = rotationAngle;
}

//Operator
bool Transform::operator==(const Transform& other) const {
	return (translateX == other.translateX && translateY == other.translateY &&
		scaleX == other.scaleX && scaleY == other.scaleY &&
		rotationAngle == other.rotationAngle);
}


bool Transform::isDefault() const {
	return translateX == 0 && translateY == 0 &&
		rotationAngle == 0 &&
		scaleX == 1 && scaleY == 1;
}
