#include "Transform.h"

//Constructor
Transform::Transform() : translateX(0), translateY(0), scaleX(1), scaleY(1), rotationAngle(0) {}

Transform::Transform(float translateX, float translateY, float scaleX, float scaleY, float rotationAngle)
			: translateX(translateX), translateY(translateY), scaleX(scaleX), scaleY(scaleY), rotationAngle(rotationAngle) {}

<<<<<<< HEAD
void Transform::apply(Gdiplus::Matrix& parentMatrix, PointSVG center) const 
{
    Gdiplus::Matrix matrix;

    // Dịch chuyển tới vị trí gốc
    matrix.Translate(translateX, translateY);

    // Xoay quanh tâm
    matrix.Translate(center.getX(), center.getY());  // Dịch chuyển đến tâm
    matrix.Rotate(rotationAngle);                     // Xoay quanh tâm
    matrix.Translate(-center.getX(), -center.getY()); // Trở lại vị trí ban đầu

    // Thay đổi tỉ lệ (scale)
    matrix.Scale(scaleX, scaleY);

    // Áp dụng phép biến đổi cho ma trận cha
    parentMatrix.Multiply(&matrix);
}




=======
//Apply tranform
void Transform::apply(Gdiplus::Graphics& graphics, PointSVG center) const {
    Gdiplus::Matrix matrix;

    // Dịch chuyển
    matrix.Translate(translateX, translateY);

    // Xoay quanh tâm
    matrix.Translate(center.getX(), center.getY());
    matrix.Rotate(rotationAngle);
    
    // Thay đổi tỉ lệ
    matrix.Scale(scaleX, scaleY);

    // Đưa về vị trí ban đầu
    matrix.Translate(-center.getX(), -center.getY());

    // Thiết lập ma trận biến đổi
    graphics.SetTransform(&matrix);
}

//Load tranform from file
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
Transform Transform::loadTransform(rapidxml::xml_node<>* node) {
    Transform transform;
    rapidxml::xml_attribute<>* transformAttr = node->first_attribute("transform");

    if (transformAttr) {
        std::string transformStr = transformAttr->value();
<<<<<<< HEAD
        std::regex regex("(\\w+)\\s*\\(([^)]+)\\)");
=======

        // Regex để phân tích cú pháp các lệnh trong "transform"
        std::regex regex("(\\w+)\\(([^)]+)\\)");
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
        std::smatch match;

        while (std::regex_search(transformStr, match, regex)) {
            std::string command = match[1].str();
            std::string values = match[2].str();

<<<<<<< HEAD
            parseCommand(command, values, transform);
=======
            if (command == "translate") {
                float translateX = 0.0f, translateY = 0.0f;

                if (sscanf_s(values.c_str(), "%f", &translateX) == 1) {
                    translateY = 0.0f; // translate(x) -> translate(x, 0)
                }

                transform.setTranslateX(translateX);
                transform.setTranslateY(translateY);
            }

            else if (command == "scale") {
                float scaleX = 1.0f, scaleY = 1.0f;

                if (sscanf_s(values.c_str(), "%f", &scaleX) == 1) {
                    scaleY = scaleX; // scale(s) -> scale(s, s)
                }
                
                transform.setScaleX(scaleX);
                transform.setScaleY(scaleY);
            }

            else if (command == "rotate") {
                float angle = 0.0f;
                sscanf_s(values.c_str(), "%f", &angle);
                transform.setRotationAngle(angle);
            }
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f

            transformStr = match.suffix().str();
        }
    }

    return transform;
}

<<<<<<< HEAD
void Transform::parseCommand(const std::string& command, const std::string& values, Transform& transform) {
    if (command == "translate") {
        float translateX = 0.0f, translateY = 0.0f;
        std::stringstream ss(values);
        ss >> translateX;
        ss.ignore();
        if (!(ss >> translateY)) translateY = 0.0f;
        transform.setTranslateX(translateX);
        transform.setTranslateY(translateY);
    } else if (command == "scale") {
        float scaleX = 1.0f, scaleY = 1.0f;
        std::stringstream ss(values);
        ss >> scaleX;
        ss.ignore();
        if (!(ss >> scaleY)) scaleY = scaleX;
        transform.setScaleX(scaleX);
        transform.setScaleY(scaleY);
    } else if (command == "rotate") {
        float angle = 0.0f, cx = 0.0f, cy = 0.0f;
        std::stringstream ss(values);
        ss >> angle;
        if (ss >> cx >> cy) {
            // Có thể lưu cx, cy nếu cần
        }
        transform.setRotationAngle(angle);
    }
}


=======
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
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

<<<<<<< HEAD

bool Transform::isDefault() const 
{
    return translateX == 0 && translateY == 0 &&
           rotationAngle == 0 &&
           scaleX == 1 && scaleY == 1;
}
=======
void Transform::combine(Gdiplus::Graphics& graphics) const {
    Gdiplus::Matrix matrix;

    // Dịch chuyển
    matrix.Translate(translateX, translateY);

    // Xoay quanh tâm
    matrix.Rotate(rotationAngle);

    // Thay đổi tỉ lệ
    matrix.Scale(scaleX, scaleY);

    graphics.MultiplyTransform(&matrix);
}

std::ostream& operator<<(std::ostream& os, const Transform& transform) {
	os << "Translate: (" << transform.getTranslateX() << ", " << transform.getTranslateY() << ") "
	   << "Scale: (" << transform.getScaleX() << ", " << transform.getScaleY() << ") "
	   << "Rotation: " << transform.getRotationAngle();
	return os;
}
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
