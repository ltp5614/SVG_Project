#ifndef GRADIENT_MANAGER_H
#define GRADIENT_MANAGER_H

#include <map>
#include <string>
#include <memory>
#include "Gradient.h"
#include "rapidxml.hpp"

class GradientManager {
private:
    std::map<std::string, std::shared_ptr<Gradient>> gradients; // Lưu trữ gradient với ID

public:
    void parseGradients(rapidxml::xml_node<>* defsNode); // Phân tích cú pháp <defs>
    const Gradient* getGradient(const std::string& id) const; // Lấy gradient theo ID
    std::pair<std::string, float> parseStopColorAndOpacity(const std::string& input);
    float parseOffset(const std::string& offsetStr);
    void printAllGradients() const;
};

#endif
