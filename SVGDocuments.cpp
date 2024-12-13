#include "SVGDocuments.h"

SVGDocuments SVGDocuments::loadFile(const std::string& filePath) {
    SVGDocuments list;

    // Read XML file into buffer
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Cannot open file: " << filePath << std::endl;
        return list;
    }

    std::cout << "File " << filePath << " opened successfully" << std::endl;

    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0'); // Null terminator

    // Parse the buffer into an XML document
    xml_document<> doc;

    try {
        doc.parse<0>(&buffer[0]);
    }

    catch (const parse_error& e) {
        std::cout << "Error when handling XML file: " << e.what() << std::endl;
        return list;
    }

    // Get the root node
    xml_node<>* rootNode = doc.first_node();
    if (!rootNode) {
        std::cout << "XML file empty" << std::endl;
        return list;
    }

    // Traverse each child node
    for (xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()) {
        if (!node) {
            continue;
        }

        // Get shape
        std::string nodeName = node->name();

        // 7 basic cases
        // 1. Rectangle
        if (nodeName == "rect") {
            // Read rectangle's attributes
            int x = node->first_attribute("x") ? std::stoi(node->first_attribute("x")->value()) : 0;
            int y = node->first_attribute("y") ? std::stoi(node->first_attribute("y")->value()) : 0;
            int width = node->first_attribute("width") ? std::stoi(node->first_attribute("width")->value()) : 0;
            int height = node->first_attribute("height") ? std::stoi(node->first_attribute("height")->value()) : 0;
            std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
            std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
            double fill_opacity = node->first_attribute("fill-opacity") ? std::stod(node->first_attribute("fill-opacity")->value()) : 0;
            int stroke_width = node->first_attribute("stroke-width") ? std::stoi(node->first_attribute("stroke-width")->value()) : 0;

            // Create a rectangle object
            std::unique_ptr<Rect> rect = std::make_unique<Rect>(x, y, width, height, fill, fill_opacity, stroke, stroke_width);

            // Add a new rectangle element into SVGDocuments
            list.addElement(std::move(rect));
        }

        // 2. Circle
        else if (nodeName == "circle") {
            // Read circle's attributes
            int centerX = node->first_attribute("cx") ? std::stoi(node->first_attribute("cx")->value()) : 0;
            int centerY = node->first_attribute("cy") ? std::stoi(node->first_attribute("cy")->value()) : 0;
            int radius = node->first_attribute("r") ? std::stoi(node->first_attribute("r")->value()) : 0;
            double fill_opacity = node->first_attribute("fill_opacity") ? std::stod(node->first_attribute("fill_opacity")->value()) : 0;
            int stroke_width = node->first_attribute("stroke_width") ? std::stoi(node->first_attribute("stroke_width")->value()) : 0;
            double stroke_opacity = node->first_attribute("stroke_opacity") ? std::stod(node->first_attribute("stroke_opacity")->value()) : 0;
            std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
            std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";

            // Create a circle object
            std::unique_ptr<Circle> circle = std::make_unique<Circle>(centerX, centerY, radius, fill, fill_opacity, stroke, stroke_width, stroke_opacity);

            // Add a new circle element into SVGDocument
            list.addElement(std::move(circle));
        }

        // 3. Ellipse
        else if (nodeName == "ellipse") {
            // Read ellipse's attributes
            int centerX = node->first_attribute("cx") ? std::stoi(node->first_attribute("cx")->value()) : 0;
            int centerY = node->first_attribute("cy") ? std::stoi(node->first_attribute("cy")->value()) : 0;
            int radiusX = node->first_attribute("rx") ? std::stoi(node->first_attribute("rx")->value()) : 0;
            int radiusY = node->first_attribute("ry") ? std::stoi(node->first_attribute("ry")->value()) : 0;
            double fill_opacity = node->first_attribute("fill_opacity") ? std::stod(node->first_attribute("fill_opacity")->value()) : 0;
            int stroke_width = node->first_attribute("stroke_width") ? std::stoi(node->first_attribute("stroke_width")->value()) : 0;
            double stroke_opacity = node->first_attribute("stroke_opacity") ? std::stod(node->first_attribute("stroke_opacity")->value()) : 0;
            std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
            std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
            
            // Create an ellipse object
            std::unique_ptr<Ellipse> ellipse = std::make_unique<Ellipse>(centerX, centerY, radiusX, radiusY, fill, fill_opacity, stroke, stroke_width, stroke_opacity);

            // Add a new ellipse element into SVGDocument
            list.addElement(std::move(ellipse));
        }

        // 4. Text
        else if (nodeName == "text") {
            // Read text's attributes
            int x = node->first_attribute("x") ? std::stoi(node->first_attribute("x")->value()) : 0;
            int y = node->first_attribute("y") ? std::stoi(node->first_attribute("y")->value()) : 0;
            std::string content = node->value() ? node -> value() : "none";
            std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
            int fontSize = node->first_attribute("font-size") ? std::stoi(node->first_attribute("font-size")->value()) : 0;

            // Create a text object
            std::unique_ptr<Text> text = std::make_unique<Text>(x, y, fontSize, content, fill);

            // Add a new text element into SVGDocument
            list.addElement(std::move(text));
        }

        // 5. Line
        else if (nodeName == "line") {
            // Read line's attributes
            int x1 = node->first_attribute("x1") ? std::stoi(node->first_attribute("x1")->value()) : 0;
            int y1 = node->first_attribute("y1") ? std::stoi(node->first_attribute("y1")->value()) : 0;
            int x2 = node->first_attribute("x2") ? std::stoi(node->first_attribute("x2")->value()) : 0;
            int y2 = node->first_attribute("y2") ? std::stoi(node->first_attribute("y2")->value()) : 0;
            std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
            int stroke_width = node->first_attribute("stroke-width") ? std::stoi(node->first_attribute("stroke-width")->value()) : 0;
            double stroke_opacity = node->first_attribute("stroke-opacity") ? std::stod(node->first_attribute("stroke-opacity")->value()) : 0;


            // Create a line object
            std::unique_ptr<Line> line = std::make_unique<Line>(x1, y1, x2, y2, stroke, stroke_width, stroke_opacity);

            // Add a new line element into SVGDocument
            list.addElement(std::move(line));
        }

        // 6. Polygon
        else if(nodeName == "polygon") {
			// Read polygon's attributes
			std::string pointsData = node->first_attribute("points") ? node->first_attribute("points")->value() : "";
            std::vector<std::pair<int, int>> points = parsePoints(pointsData);
			std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
			std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
            double fill_opacity = node->first_attribute("fill-opacity") ? std::stod(node->first_attribute("fill-opacity")->value()) : 0;
            int stroke_width = node->first_attribute("stroke-width") ? std::stoi(node->first_attribute("stroke-width")->value()) : 0;
            double stroke_opacity = node->first_attribute("stroke-opacity") ? std::stod(node->first_attribute("stroke-opacity")->value()) : 0;

            // Create a polygon object
			std::unique_ptr<Polygon> polygon = std::make_unique<Polygon>(points, fill, fill_opacity, stroke, stroke_width, stroke_opacity);

			// Add a new polygon element into SVGDocument
			list.addElement(std::move(polygon));
		}

        // 7. Polyline
        else if (nodeName == "polyline") {
            //Read polyline's attributes
            std::string pointsData = node->first_attribute("points") ? node->first_attribute("points")->value() : "";
            std::vector<std::pair<int, int>> points = parsePoints(pointsData);
            std::string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
            double fill_opacity = node->first_attribute("fill-opacity") ? std::stod(node->first_attribute("fill-opacity")->value()) : 0;
            std::string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";
            int stroke_width = node->first_attribute("stroke-width") ? std::stoi(node->first_attribute("stroke-width")->value()) : 0;
            double stroke_opacity = node->first_attribute("stroke-opacity") ? std::stod(node->first_attribute("stroke-opacity")->value()) : 0;

            //Create a polyline object
            std::unique_ptr<Polyline> polyline = std::make_unique<Polyline>(points, fill, fill_opacity, stroke, stroke_width, stroke_opacity);

            //Add a new polyline element into SVGDocument
            list.addElement(std::move(polyline));
        }
    }

    std::cout << "Read file successfully" << std::endl;

    return list;
}

void SVGDocuments::addElement(std::unique_ptr<SVGElements> element) {
    if (element) {
        elements.push_back(std::move(element));
    }
    else {
		std::cout << "Element is null" << std::endl;
	}
    
}

void SVGDocuments::modifyElement(int elementId, std::unique_ptr<SVGElements> newElement) {
    if (elementId >= 0 && elementId < elements.size()) {
        elements[elementId] = std::move(newElement);
    }
}

void SVGDocuments::removeElement(int elementId) {
    if (elementId >= 0 && elementId < elements.size()) {
        elements.erase(elements.begin() + elementId);
    }
}

std::vector<std::unique_ptr<SVGElements>>& SVGDocuments::getElements() {
    return elements;
}

std::vector<std::pair<int, int>> parsePoints(const std::string& pointsStr) {
    std::vector<std::pair<int, int>> points;
    std::istringstream ss(pointsStr);
    std::string point;

    while (getline(ss, point, ' ')) {
        int x, y;
        char comma;
        std::istringstream pointStream(point);

        if (pointStream >> x >> comma >> y && comma == ',') {
            points.emplace_back(x, y);
        }
    }

    return points;
}

void SVGDocuments::render() const {
    std::cout << "Render called" << std::endl;
	
    if (elements.empty()) {
		std::cout << "No elements to render" << std::endl;

		return;
	}

    for (const auto& element : elements) {
        if (element) {
            element->render();
        }

        else {
			std::cout << "Element is null" << std::endl;
		}
	}
}