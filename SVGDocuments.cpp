// SVGDocuments.cpp

#include "SVGDocuments.h"
#include "Factory.h"

SVGDocuments SVGDocuments::loadFile(const std::string& filePath, Viewbox* viewbox) {
    SVGDocuments list;
    SVGFactoryRegistry factoryRegistry;
    SVGFactoryRegistrar factoryRegister;

    factoryRegister.registerFactories(factoryRegistry);

    // Read XML file into buffer
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Cannot open file: " << filePath << std::endl;
        return list;
    }

    std::cout << "File " << filePath << " opened successfully" << std::endl;

    file.seekg(0, std::ios::end);
    size_t fileSize = static_cast<size_t>(file.tellg());
    file.seekg(0, std::ios::beg);

    // Use heap-allocated buffer
    std::vector<char> buffer;
    buffer.reserve(fileSize + 1); // Allocate space for the file + null terminator
    buffer.insert(buffer.end(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    buffer.push_back('\0'); // Null terminator

    // Parse the buffer into an XML document
    rapidxml::xml_document<> doc;

    try {
        doc.parse<0>(&buffer[0]);
    }
    catch (const rapidxml::parse_error& e) {
        std::cout << "Error when handling XML file: " << e.what() << std::endl;
        return list;
    }

    // Get the root node
    rapidxml::xml_node<>* rootNode = doc.first_node();
    viewbox->parseViewbox(rootNode);

    if (!rootNode) {
        std::cout << "XML file empty" << std::endl;
        return list;
    }

    // Traverse each child node and create elements using the factory
    for (rapidxml::xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()) {
        std::string nodeName = node->name();
        std::unique_ptr<SVGElements> element = factoryRegistry.createElementFromFactory(nodeName, node);

        if (element) {
            list.addElement(std::move(element));
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

std::vector<std::pair<float, float>> parsePoints(const std::string& pointsStr) {
    std::vector<std::pair<float, float>> points;

    // Kiểm tra xem chuỗi có chứa dấu phẩy ',' không
    bool hasComma = pointsStr.find(',') != std::string::npos;

    if (hasComma) {
        // Định dạng x,y x,y ...
        std::istringstream ss(pointsStr);
        std::string point;

        while (std::getline(ss, point, ' ')) {
            float x, y;
            char comma;
            std::istringstream pointStream(point);

            if (pointStream >> x >> comma >> y && comma == ',') {
                points.emplace_back(x, y);
            }
        }
    } else {
        // Định dạng x y x y ...
        std::istringstream ss(pointsStr);
        std::vector<float> coords;
        float value;

        // Tách các giá trị float
        while (ss >> value) {
            coords.push_back(value);
        }

        // Ghép từng cặp thành (x, y)
        for (size_t i = 0; i + 1 < coords.size(); i += 2) {
            points.emplace_back(coords[i], coords[i + 1]);
        }
    }

    return points;
}

void SVGDocuments::render(Graphics& graphics) const {
    std::cout << "Render called" << std::endl;

    if (elements.empty()) {
        std::cout << "No elements to render" << std::endl;
        return;
    }

    Gdiplus::Matrix matrix;
    for (const auto& element : elements) {
        if (element) {
            element->render(graphics, matrix);
        } else {
            std::cout << "Element is null" << std::endl;  // In ra nếu element bị null
        }
    }
}
