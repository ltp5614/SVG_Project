#include "GradientManager.h"
#include <iostream>



void GradientManager::parseGradients(rapidxml::xml_node<>* defsNode) {
    for (auto gradientNode = defsNode->first_node(); gradientNode; gradientNode = gradientNode->next_sibling()) {
        std::string nodeName = gradientNode->name();

        if (nodeName == "linearGradient") {
            std::string id = gradientNode->first_attribute("id") ? gradientNode->first_attribute("id")->value() : "";

            std::string x1 = gradientNode->first_attribute("x1") ? gradientNode->first_attribute("x1")->value() : "0";
            std::string x2 = gradientNode->first_attribute("x2") ? gradientNode->first_attribute("x2")->value() : "1";
            std::string y1 = gradientNode->first_attribute("y1") ? gradientNode->first_attribute("y1")->value() : "0";
            std::string y2 = gradientNode->first_attribute("y2") ? gradientNode->first_attribute("y2")->value() : "0";

            auto linearGradient = std::make_unique<LinearGradient>(x1, y1, x2, y2);

            for (auto stopNode = gradientNode->first_node("stop"); stopNode; stopNode = stopNode->next_sibling("stop")) {
              std::string offsetStr = stopNode->first_attribute("offset") ? stopNode->first_attribute("offset")->value() : "0";
              float offset = parseOffset(offsetStr);

              // Kiểm tra và xử lý thuộc tính "style"
              std::string color, opacityStr;
              float opacity = 1.0f; // Giá trị mặc định cho độ trong suốt

              if (auto styleAttr = stopNode->first_attribute("style")) {
                  // Phân tích chuỗi style
                  std::pair<std::string, float> h = parseStopColorAndOpacity(styleAttr->value());
                  color = h.first;
                  opacity = h.second;
              } else {
                  // Xử lý riêng "stop-color" và "stop-opacity"
                  color = stopNode->first_attribute("stop-color") ? stopNode->first_attribute("stop-color")->value() : "none";
                  if (auto opacityAttr = stopNode->first_attribute("stop-opacity")) {
                      try {
                          opacity = std::stof(opacityAttr->value());
                      } catch (...) {
                          opacity = 1.0f; // Giá trị mặc định nếu chuyển đổi thất bại
                      }
                  }
              }

              // Thêm điểm dừng gradient
              linearGradient->addStop(offset, color, opacity);
          }
          gradients[id] = std::move(linearGradient);
        }

        // Xử lý radialGradient tương tự
        else if (nodeName == "radialGradient") {
            std::string id = gradientNode->first_attribute("id") ? gradientNode->first_attribute("id")->value() : "";

            // Lấy các giá trị cx, cy, r (nếu không tồn tại thì gán giá trị mặc định)
            std::string cx = gradientNode->first_attribute("cx") ? gradientNode->first_attribute("cx")->value() : "50%";
            std::string cy = gradientNode->first_attribute("cy") ? gradientNode->first_attribute("cy")->value() : "50%";
            std::string r = gradientNode->first_attribute("r") ? gradientNode->first_attribute("r")->value() : "50%";


            auto radialGradient = std::make_unique<RadialGradient>(cx, cy, r);

        for (auto stopNode = gradientNode->first_node("stop"); stopNode; stopNode = stopNode->next_sibling("stop")) {
            std::string offsetStr = stopNode->first_attribute("offset") ? stopNode->first_attribute("offset")->value() : "0";
            float offset = parseOffset(offsetStr);

            // Kiểm tra và xử lý thuộc tính "style"
            std::string color, opacityStr;
            float opacity = 1.0f; // Giá trị mặc định cho độ trong suốt

            if (auto styleAttr = stopNode->first_attribute("style")) {
                // Phân tích chuỗi style
                std::pair<std::string, float> h = parseStopColorAndOpacity(styleAttr->value());
                color = h.first;
                opacity = h.second;
            } else {
                // Xử lý riêng "stop-color" và "stop-opacity"
                color = stopNode->first_attribute("stop-color") ? stopNode->first_attribute("stop-color")->value() : "none";
                if (auto opacityAttr = stopNode->first_attribute("stop-opacity")) {
                    try {
                        opacity = std::stof(opacityAttr->value());
                    } catch (...) {
                        opacity = 1.0f; // Giá trị mặc định nếu chuyển đổi thất bại
                    }
                }
            }

            // Thêm điểm dừng gradient
            radialGradient->addStop(offset, color, opacity);
        }
            gradients[id] = std::move(radialGradient);
        }
    }
}



const Gradient* GradientManager::getGradient(const std::string& id) const {
    auto it = gradients.find(id);
    if (it != gradients.end()) {
        return it->second.get();
    }
    return nullptr;
}


std::pair<std::string, float> GradientManager::parseStopColorAndOpacity(const std::string& input) {
    size_t colorPos = input.find("stop-color:");
    size_t opacityPos = input.find("stop-opacity:");

    std::string color = "none";
    float opacity = 1.0f; // Giá trị mặc định

    // Xử lý "stop-color"
    if (colorPos != std::string::npos) {
        size_t colorEnd = input.find(';', colorPos); // Tìm dấu `;` kết thúc phần `stop-color`
        color = input.substr(colorPos + 11, colorEnd - colorPos - 11); // Tách giá trị `stop-color`
    }

    // Xử lý "stop-opacity" (nếu có)
    if (opacityPos != std::string::npos) {
        size_t opacityEnd = input.find(';', opacityPos); // Tìm dấu `;` kết thúc phần `stop-opacity`
        std::string opacityPart = input.substr(opacityPos + 13, opacityEnd - opacityPos - 13); // Tách giá trị `stop-opacity`
        try {
            opacity = std::stof(opacityPart);
        } catch (...) {
            throw std::invalid_argument("Invalid stop-opacity value.");
        }
    }

    return std::make_pair(color, opacity);
}


float GradientManager::parseOffset(const std::string& offsetStr) {
    // Kiểm tra nếu giá trị có chứa dấu "%"
    std::string processedStr = offsetStr;
    if (offsetStr.find('%') != std::string::npos) {
        // Loại bỏ ký tự "%"
        processedStr = offsetStr.substr(0, offsetStr.find('%'));
        // Chuyển giá trị phần trăm thành số thực, chia cho 100
        try {
            return std::stof(processedStr) / 100.0f;
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid offset value: " << offsetStr << ". Defaulting to 0.0f.\n";
            return 0.0f;
        } catch (const std::out_of_range&) {
            std::cerr << "Offset value out of range: " << offsetStr << ". Defaulting to 0.0f.\n";
            return 0.0f;
        }
    }

    // Nếu không có phần trăm, cố gắng chuyển đổi trực tiếp
    try {
        return std::stof(processedStr);
    } catch (const std::invalid_argument&) {
        std::cerr << "Invalid offset value: " << offsetStr << ". Defaulting to 0.0f.\n";
        return 0.0f;
    } catch (const std::out_of_range&) {
        std::cerr << "Offset value out of range: " << offsetStr << ". Defaulting to 0.0f.\n";
        return 0.0f;
    }
}


void GradientManager::printAllGradients() const 
{
    std::cout << "Listing all gradients in GradientManager:\n";

    // Duyệt qua từng gradient trong std::map
    for (const auto& pair : gradients) {
        const std::string& gradientId = pair.first;
        const std::shared_ptr<Gradient>& gradient = pair.second; // Đối tượng gradient

        std::cout << "Gradient ID: " << gradientId << "\n";
        
        // In ra các stop của gradient
        for (const auto& stop : gradient->getStops()) {  // Giả sử Gradient có phương thức getStops()
            std::cout << "    Stop: offset = " << stop.offset
                      << ", color = " << stop.color
                      << ", opacity = " << stop.opacity << "\n";
        }
    }
}


