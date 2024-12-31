//Factory.cpp

#include "Factory.h"
#include "SVGDocuments.h"

// Factory for creating rectangles
std::unique_ptr<SVGElements> RectFactory::createElement(rapidxml::xml_node<>* node) const {
    //Read rectangle's attributes
    float x = node->first_attribute("x") ? std::stof(node->first_attribute("x")->value()) : 0;
    float y = node->first_attribute("y") ? std::stof(node->first_attribute("y")->value()) : 0;
    float width = node->first_attribute("width") ? std::stof(node->first_attribute("width")->value()) : 0;
    float height = node->first_attribute("height") ? std::stof(node->first_attribute("height")->value()) : 0;
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 0.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 0.0f;
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";

        // Kiểm tra nếu fill là một phần của kiểu style
    if (node->first_attribute("style")) {
        std::string style = node->first_attribute("style")->value();
        auto styleMap = parseStyle(style);
        
        // Kiểm tra nếu trong style có thuộc tính fill
        if (styleMap.find("fill") != styleMap.end()) {
            fill = styleMap["fill"];
        }
    }

    Transform transform = Transform::loadTransform(node);

    // Create a rectangle object
    return std::make_unique<RectSVG>(x, y, width, height, fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
}

// Factory for creating circles
std::unique_ptr<SVGElements> CircleFactory::createElement(rapidxml::xml_node<>* node) const {
    // Read circle's attributes
    float centerX = node->first_attribute("cx") ? std::stof(node->first_attribute("cx")->value()) : 0;
    float centerY = node->first_attribute("cy") ? std::stof(node->first_attribute("cy")->value()) : 0;
    float radius = node->first_attribute("r") ? std::stof(node->first_attribute("r")->value()) : 0;
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 0.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 0.0f;
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    Transform transform = Transform::loadTransform(node);

    // Create a circle object
    return std::make_unique<CircleSVG>(centerX, centerY, radius, fill, fill_opacity, stroke, stroke_width, stroke_opacity,transform);
}

// Factory for creating ellipses
std::unique_ptr<SVGElements> EllipseFactory::createElement(rapidxml::xml_node<>* node) const {
    // Read ellipse's attributes
    float centerX = node->first_attribute("cx") ? std::stof(node->first_attribute("cx")->value()) : 0;
    float centerY = node->first_attribute("cy") ? std::stof(node->first_attribute("cy")->value()) : 0;
    float radiusX = node->first_attribute("rx") ? std::stof(node->first_attribute("rx")->value()) : 0;
    float radiusY = node->first_attribute("ry") ? std::stof(node->first_attribute("ry")->value()) : 0;
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 0.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 0.0f;
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    Transform transform = Transform::loadTransform(node);

    // Create an ellipse object
    return std::make_unique<EllipseSVG>(centerX, centerY, radiusX, radiusY, fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
}

// Factory for creating lines
std::unique_ptr<SVGElements> LineFactory::createElement(rapidxml::xml_node<>* node) const {
    // Read line's attributes
    float x1 = node->first_attribute("x1") ? std::stof(node->first_attribute("x1")->value()) : 0;
    float y1 = node->first_attribute("y1") ? std::stof(node->first_attribute("y1")->value()) : 0;
    float x2 = node->first_attribute("x2") ? std::stof(node->first_attribute("x2")->value()) : 0;
    float y2 = node->first_attribute("y2") ? std::stof(node->first_attribute("y2")->value()) : 0;
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 0.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 0.0f;
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    Transform transform = Transform::loadTransform(node);

    // Create a line object
    return std::make_unique<LineSVG>(x1, y1, x2, y2, fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
}

// Factory for creating polygons
std::unique_ptr<SVGElements> PolygonFactory::createElement(rapidxml::xml_node<>* node) const {
    // Read polygon's attributes
    std::string pointsData = node->first_attribute("points") ? node->first_attribute("points")->value() : "";
    std::vector<std::pair<float, float>> points = parsePoints(pointsData);
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 0.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 0.0f;
    Transform transform = Transform::loadTransform(node);

    // Create a line 
    return std::make_unique<PolygonSVG>(points, fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
}

// Factory for creating polylines
std::unique_ptr<SVGElements> PolylineFactory::createElement(rapidxml::xml_node<>* node) const {
    // Read polyline's attributes
    std::string pointsData = node->first_attribute("points") ? node->first_attribute("points")->value() : "";
    std::vector<std::pair<float, float>> points = parsePoints(pointsData);
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 0.0f;
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 0.0f;
    Transform transform = Transform::loadTransform(node);

    // Create a polyline object
    return std::make_unique<PolylineSVG>(points, fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
}

// Factory for creating paths
std::unique_ptr<SVGElements> PathFactory::createElement(rapidxml::xml_node<>* node) const {
    // Read path's attributes
    std::string pointsData = node->first_attribute("d") ? node->first_attribute("d")->value() : "";
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 0.0f;
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 0.0f;
    Transform transform = Transform::loadTransform(node);

    // Create a path object
    return std::make_unique<PathSVG>(pointsData, fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
}

// Factory for creating texts
std::unique_ptr<SVGElements> TextFactory::createElement(rapidxml::xml_node<>* node) const {
    // Read text's attributes
    float x = node->first_attribute("x") ? std::stof(node->first_attribute("x")->value()) : 0;
    float y = node->first_attribute("y") ? std::stof(node->first_attribute("y")->value()) : 0;
    float dx = node->first_attribute("dx") ? std::stof(node->first_attribute("dx")->value()) : 0;
    float dy = node->first_attribute("dy") ? std::stof(node->first_attribute("dy")->value()) : 0;
    std::string content = node->value() ? node -> value() : "none";
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 0.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 0.0f;
    float fontSize = node->first_attribute("font-size") ? std::stof(node->first_attribute("font-size")->value()) : 0;
    std::string fontFamily = node->first_attribute("font-family") ? node->first_attribute("font-family")->value() : "Times New Roman";
    std::wstring font = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(fontFamily);
    
    // Read font-style and text-anchor
    std::string fontStyle = node->first_attribute("font-style") ? node->first_attribute("font-style")->value() : "normal";
    std::string textAnchor = node->first_attribute("text-anchor") ? node->first_attribute("text-anchor")->value() : "start";
    
    // Load transform
    Transform transform = Transform::loadTransform(node);

    // Create a text object with additional attributes
    return std::make_unique<TextSVG>(x, y, dx, dy, fontSize, content, font, textAnchor, fontStyle, fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
}


// Factory for creating group
std::unique_ptr<SVGElements> GroupFactory::createElement(rapidxml::xml_node<>* node) const 
{
    //Read group's attributes
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 0.0f;
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 0.0f;
    Transform transform = Transform::loadTransform(node);
    float font_size = node->first_attribute("font-size") ? std::stof(node->first_attribute("font-size")->value()) : 0.0f;


    std::vector<std::unique_ptr<SVGElements>> elements;
    
    SVGFactoryRegistry factoryRegistry;
    SVGFactoryRegistrar factoryRegister;

    factoryRegister.registerAllFactories(factoryRegistry);

    // Duyệt qua các con trong nhóm (group)
    for (auto childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) {
      if (!childNode) {
          std::cout << "No child node found.\n";
          continue;
      }
      std::string elementName = childNode->name();
      if (elementName.empty()) {
          std::cout << "[Unnamed Node]\n";
          continue;
      }

      if (elementName == "g") {
        // Kế thừa thuộc tính của group cha cho group con
        auto group = createElement(childNode);
        if (group) {

            // Kiểm tra nếu là GroupSVG và gọi applyGroupAttributes
            if (auto groupSVG = dynamic_cast<GroupSVG*>(group.get())) {
                groupSVG->inheritedAttributes(fill, fill_opacity, 
               stroke, stroke_width, stroke_opacity, transform, font_size);
                groupSVG->applyGroupAttributes();
            }

            elements.push_back(std::move(group));
        }

      } else {
          auto element = factoryRegistry.createElementFromFactory(elementName, childNode);
          if (element) {
              elements.push_back(std::move(element));
          }
      }
  }
    // Tạo đối tượng GroupSVG với các phần tử con
std::unique_ptr<GroupSVG> GroupFinal = std::make_unique<GroupSVG>(
    std::move(elements), fill, fill_opacity, 
    stroke, stroke_width, stroke_opacity, transform, font_size);

    GroupFinal->applyGroupAttributes();
    return GroupFinal;
}

// Registry for SVG element factories
void SVGFactoryRegistry::registerFactory(const std::string& name, std::function<std::unique_ptr<SVGElements>(rapidxml::xml_node<>* node)> factory) {
    factoryMap[name] = std::move(factory);
}

// Create an element using the factory
std::unique_ptr<SVGElements> SVGFactoryRegistry::createElementFromFactory(const std::string& name, rapidxml::xml_node<>* node) {
    auto it = factoryMap.find(name);
    
    if (it != factoryMap.end()) {
        return it->second(node);
    }

    else {
        std::cout << "Factory not found for: " << name << std::endl;

        return nullptr;
    }
}

// Register factories
void SVGFactoryRegistrar::registerAllFactories(SVGFactoryRegistry& registry) {
	registerFactories<RectFactory>(registry, "rect");
    registerFactories<CircleFactory>(registry, "circle");
    registerFactories<EllipseFactory>(registry, "ellipse");
    registerFactories<LineFactory>(registry, "line");
    registerFactories<PathFactory>(registry, "path");
    registerFactories<PolygonFactory>(registry, "polygon");
    registerFactories<PolylineFactory>(registry, "polyline");
    registerFactories<TextFactory>(registry, "text");
    registerFactories<GroupFactory>(registry, "g");
}


std::unordered_map<std::string, std::string> parseStyle(const std::string& style) {
    std::unordered_map<std::string, std::string> styleMap;
    std::istringstream styleStream(style);  // Tạo một stream từ chuỗi style
    std::string token;

    // Đọc từng cặp khóa-giá trị từ chuỗi style
    while (std::getline(styleStream, token, ';')) {
        // Tìm vị trí dấu ':', phân tách khóa và giá trị
        size_t pos = token.find(':');
        if (pos != std::string::npos) {
            std::string key = token.substr(0, pos);   // Lấy phần trước dấu ':'
            std::string value = token.substr(pos + 1); // Lấy phần sau dấu ':'
            
            // Loại bỏ khoảng trắng thừa ở đầu và cuối key và value
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(value.find_last_not_of(" \t") + 1);

            // Lưu vào map
            styleMap[key] = value;
        }
    }

    return styleMap;
}
