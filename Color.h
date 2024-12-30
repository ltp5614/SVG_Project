#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <regex>
#include <tuple>

class ColorSVG {
   private:
       int red, blue, green;
       float alpha; // Transparency (default: 255)

   public:
       ColorSVG(int red, int blue, int green, float alpha = 1.0);
       static ColorSVG parseColor(const std::string& colorStr);
       
       int getRed();
       int getBlue();
       int getGreen();
       float getAlpha();

       static const std::unordered_map<std::string, std::tuple<int, int, int>> colorMap;
};

bool isValidColor(int color);

#endif
