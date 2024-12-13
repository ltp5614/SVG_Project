#include "Color.h"

ColorSVG::ColorSVG(int red, int green, int blue, float alpha) 
	: red(red), green(green), blue(blue),alpha(alpha) {}

int ColorSVG::getRed() {
	return red;
}

int ColorSVG::getGreen() {
	return green;
}

int ColorSVG::getBlue() {
	return blue;
}

float ColorSVG::getAlpha() {
	return alpha;
}

ColorSVG ColorSVG::parseColor(const std::string& colorStr) {
    auto it = colorMap.find(colorStr);
    if (it != colorMap.end()) {
        auto color = it->second;
        int r = std::get<0>(color);
        int g = std::get<1>(color);
        int b = std::get<2>(color);

        return ColorSVG(r, g, b, 1.0f); // Mặc định alpha = 1.0
    }

    // Kiểm tra định dạng rgb(r, g, b)
    if (colorStr.find("rgb") == 0) {
        int red = 0, green = 0, blue = 0;
        float alpha = 1.0; // Transparency (mặc định: 1.0)

        size_t start = colorStr.find("(");
        size_t end = colorStr.find(")");

        if (start == std::string::npos || end == std::string::npos) {
            std::cout << "Invalid color data" << std::endl;
            return ColorSVG(-1, -1, -1, -1.0);
        }

        std::string content = colorStr.substr(start + 1, end - start - 1);
        std::stringstream ss(content);
        std::string temp;

        getline(ss, temp, ',');
        red = stoi(temp);
        getline(ss, temp, ',');
        green = stoi(temp);
        getline(ss, temp);
        blue = stoi(temp);

        return ColorSVG(red, green, blue, alpha);
    }

    // Kiểm tra định dạng #RRGGBB hoặc #RGB
    if (colorStr[0] == '#') {
        std::string hex = colorStr.substr(1); // Bỏ ký tự #
        if (hex.size() == 3) {
            // Dạng rút gọn #RGB -> mở rộng thành #RRGGBB
            hex = std::string(2, hex[0]) + std::string(2, hex[1]) + std::string(2, hex[2]);
        }

        if (hex.size() != 6) {
            std::cout << "Invalid hex color data" << std::endl;
            return ColorSVG(-1, -1, -1, -1.0);
        }

        // Chuyển đổi từng cặp ký tự hex sang số nguyên
        int red = stoi(hex.substr(0, 2), nullptr, 16);
        int green = stoi(hex.substr(2, 2), nullptr, 16);
        int blue = stoi(hex.substr(4, 2), nullptr, 16);
        float alpha = 1.0; // Transparency (mặc định: 1.0)

        return ColorSVG(red, green, blue, alpha);
    }

    // Nếu không khớp định dạng nào
    std::cout << "Unsupported color format: " << colorStr << std::endl;
    return ColorSVG(-1, -1, -1, -1.0);
}

bool isValidColor(int color) {
    return (color >= 0 && color <= 255);
}

const std::unordered_map<std::string, std::tuple<int, int, int>> ColorSVG::colorMap = {
    {"red", {255, 0, 0}},
    {"green", {0, 255, 0}},
    {"blue", {0, 0, 255}},
    {"black", {0, 0, 0}},
    {"white", {255, 255, 255}},
    {"yellow", {255, 255, 0}},
    {"cyan", {0, 255, 255}},
    {"magenta", {255, 0, 255}},
    {"gray", {128, 128, 128}},
    {"grey", {128, 128, 128}},
    {"darkslategray", {47, 79, 79}},
	{"darkslategrey", {47, 79, 79}},
    {"midnightblue", {25, 25, 112}}
};