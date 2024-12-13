#include "Element.h"

SVGDocuments readXMLFile(const string& filePath) {
    SVGDocuments list;

    // Read XML file into buffer
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Cannot open file: " << filePath << endl;
        return list;
    }

    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0'); // Null terminator

    // Parse the buffer into an XML document
    xml_document<> doc;

    try {
        doc.parse<0>(&buffer[0]);
    }
    catch (const parse_error& e) {
        cout << "Error when handling XML file: " << e.what() << endl;
        return list;
    }

    // Get the root node
    xml_node<>* rootNode = doc.first_node();
    if (!rootNode) {
        cout << "XML file empty" << endl;
        return list;
    }

    // Traverse each child node
    for (xml_node<>* node = rootNode->first_node(); node; node = node->next_sibling()) {
        if (!node) {
            continue;
        }

        // Get shape
        string nodeName = node->name();

        cout << "Reading node: " << nodeName << endl;

        // 7 basic cases
        // 1. Rect
        if (nodeName == "rect") {
            // Read rectangle's attributes safely
            int x = node->first_attribute("x") ? stoi(node->first_attribute("x")->value()) : 0;
            int y = node->first_attribute("y") ? stoi(node->first_attribute("y")->value()) : 0;
            int width = node->first_attribute("width") ? stoi(node->first_attribute("width")->value()) : 0;
            int height = node->first_attribute("height") ? stoi(node->first_attribute("height")->value()) : 0;
            string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
            string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";

            // Create a rectangle object
            Rect* rect = new Rect(x, y, width, height, fill, stroke);
            cout << "phong gay";
            //// Add a new rect element into SVGDocuments
            list.addElement(rect);
        }
        // 2. Circle
        else if (nodeName == "circle") {
            // Read circle's attributes safely
            int centerX = node->first_attribute("cx") ? stoi(node->first_attribute("cx")->value()) : 0;
            int centerY = node->first_attribute("cy") ? stoi(node->first_attribute("cy")->value()) : 0;
            int radius = node->first_attribute("r") ? stoi(node->first_attribute("r")->value()) : 0;
            string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";

            // Create a circle object
            Circle* circle = new Circle(centerX, centerY, radius, fill);
            // Add a new circle element into SVGDocument
            list.addElement(circle);
        }
        // 3. Ellipse
        else if (nodeName == "ellipse") {
            // Read ellipse's attributes safely
            int centerX = node->first_attribute("cx") ? stoi(node->first_attribute("cx")->value()) : 0;
            int centerY = node->first_attribute("cy") ? stoi(node->first_attribute("cy")->value()) : 0;
            int radiusX = node->first_attribute("rx") ? stoi(node->first_attribute("rx")->value()) : 0;
            int radiusY = node->first_attribute("ry") ? stoi(node->first_attribute("ry")->value()) : 0;
            string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
            string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";

            // Create an ellipse object
            Ellipse* ellipse = new Ellipse(centerX, centerY, radiusX, radiusY, fill, stroke);
            // Add a new ellipse element into SVGDocument
            list.addElement(ellipse);
        }
        // 4. Text
        else if (nodeName == "text") {
            // Read text's attributes safely
            int x = node->first_attribute("x") ? stoi(node->first_attribute("x")->value()) : 0;
            int y = node->first_attribute("y") ? stoi(node->first_attribute("y")->value()) : 0;
            string content = node->value();
            string fill = node->first_attribute("fill") ? node->first_attribute("fill")->value() : "none";
            string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";

            // Create a text object
            Text* text = new Text(x, y, content, fill, stroke);
            // Add a new text element into SVGDocument
            list.addElement(text);
        }
        // 5. Line
        else if (nodeName == "line") {
            // Read line's attributes safely
            int x1 = node->first_attribute("x1") ? stoi(node->first_attribute("x1")->value()) : 0;
            int y1 = node->first_attribute("y1") ? stoi(node->first_attribute("y1")->value()) : 0;
            int x2 = node->first_attribute("x2") ? stoi(node->first_attribute("x2")->value()) : 0;
            int y2 = node->first_attribute("y2") ? stoi(node->first_attribute("y2")->value()) : 0;
            string stroke = node->first_attribute("stroke") ? node->first_attribute("stroke")->value() : "none";

            // Create a line object
            Line* line = new Line(x1, y1, x2, y2, stroke);
            // Add a new line element into SVGDocument
            list.addElement(line);
        }
    }

    cout << "Read file successfully" << endl;

    return list;
}

int main() {
    string filePath = "sample.svg";
    SVGDocuments list;

    list = readXMLFile(filePath);

    return 0;
}
