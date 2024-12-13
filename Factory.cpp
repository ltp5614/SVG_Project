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
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 1.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 1.0f;
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
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
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 1.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 1.0f;
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
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 1.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 1.0f;
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
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 1.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 1.0f;
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    Transform transform = Transform::loadTransform(node);

    // Create a line object
    return std::make_unique<LineSVG>(x1, y1, x2, y2, fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
}

// Factory for creating polygons
std::unique_ptr<SVGElements> PolygonFactory::createElement(rapidxml::xml_node<>* node) const {
    // Read polygon's attributes
    std::string pointsData = node->first_attribute("points") ? node->first_attribute("points")->value() : "";
    std::vector<std::pair<int, int>> points = parsePoints(pointsData);
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 1.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 1.0f;
    Transform transform = Transform::loadTransform(node);

    // Create a line 
    return std::make_unique<PolygonSVG>(points, fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
}

// Factory for creating polylines
std::unique_ptr<SVGElements> PolylineFactory::createElement(rapidxml::xml_node<>* node) const {
    // Read polyline's attributes
    std::string pointsData = node->first_attribute("points") ? node->first_attribute("points")->value() : "";
    std::vector<std::pair<int, int>> points = parsePoints(pointsData);
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 1.0f;
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 1.0f;
    Transform transform = Transform::loadTransform(node);

    // Create a polyline object
    return std::make_unique<PolylineSVG>(points, fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
}

// Factory for creating paths
std::unique_ptr<SVGElements> PathFactory::createElement(rapidxml::xml_node<>* node) const {
    // Read path's attributes
    std::string pointsData = node->first_attribute("d") ? node->first_attribute("d")->value() : "";
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 1.0f;
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 1.0f;
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
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 1.0f;
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 1.0f;
    float fontSize = node->first_attribute("font-size") ? std::stof(node->first_attribute("font-size")->value()) : 0;
    std::string fontFamily = node->first_attribute("font-family") ? node->first_attribute("font-family")->value() : "Times New Roman";
    std::wstring font = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(fontFamily);
    Transform transform = Transform::loadTransform(node);

    std::cout << "Read Text" << std::endl;
    std::cout << "Content" << content << std::endl;
    std::cout << "Fill" << fill << std::endl;

    // Create a text object
    return std::make_unique<TextSVG>(x, y, dx, dy, fontSize, content, font, fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
}

// Factory for creating group
std::unique_ptr<SVGElements> GroupFactory::createElement(rapidxml::xml_node<>* node) const {
    //Read group's attributes
    std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
    float fill_opacity = node->first_attribute("fill-opacity") ? std::stof(node->first_attribute("fill-opacity")->value()) : 1.0f;
    std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
    float stroke_width = node->first_attribute("stroke-width") ? std::stof(node->first_attribute("stroke-width")->value()) : 0.0f;
    float stroke_opacity = node->first_attribute("stroke-opacity") ? std::stof(node->first_attribute("stroke-opacity")->value()) : 1.0f;
    Transform transform = Transform::loadTransform(node);
    float font_size = node->first_attribute("font-size") ? std::stof(node->first_attribute("font-size")->value()) : 0.0f;

    std::cout << "Read file: " << std::endl;
    std::cout << "Group fill: " << fill << std::endl;
    std::cout << "Group fill opacity: " << fill_opacity << std::endl;
    std::cout << "Group stroke: " << stroke << std::endl;
    std::cout << "Group stroke width: " << stroke_width << std::endl;
    std::cout << "Group stroke opacity: " << stroke_opacity << std::endl;
    std::cout << "Group transform: " << transform << std::endl;
    std::cout << "Group font size: " << font_size << std::endl;

    std::vector<std::unique_ptr<SVGElements>> elements;
    
    SVGFactoryRegistry factoryRegistry;
    SVGFactoryRegistrar factoryRegister;

    factoryRegister.registerFactories(factoryRegistry);

    GroupAttributes groupAttributes(fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform, font_size);

    // Duyệt qua các con trong nhóm (group)
    for (auto childNode = node->first_node(); childNode; childNode = childNode->next_sibling()) {
        std::string elementName = childNode->name();

        if(elementName == "g") {
            // Nếu là nhóm, gọi đệ quy để xử lý nhóm lồng
            std::unique_ptr<SVGElements> group = createElement(childNode); // Gọi lại createElement cho nhóm con
            
            if (group) {
                if (auto groupElement = dynamic_cast<GroupSVG*>(group.get())) {
					groupElement->applyGroupAttributes(fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform, font_size);
				}

                elements.push_back(std::move(group));
            }
        }

        else {
            std::unique_ptr<SVGElements> element = factoryRegistry.createElementFromFactory(elementName, childNode);

            if (element) {
                element->applyAttributes(fill, fill_opacity, stroke, stroke_width, stroke_opacity, transform);
                elements.push_back(std::move(element));
            }
        }
    }

    // Tạo đối tượng GroupSVG với các phần tử con
    return std::make_unique<GroupSVG>(std::move(elements), groupAttributes);
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
void SVGFactoryRegistrar::registerFactories(SVGFactoryRegistry& registry) {
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