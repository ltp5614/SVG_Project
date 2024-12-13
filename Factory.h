#ifndef FACTORY_H
#define FACTORY_H

#include "Circle.h"
#include "Rect.h"
#include "Line.h"
#include "Path.h"
#include "Text.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "Polyline.h"
#include "Group.h"
#include "Transform.h"
#include <memory>
#include <unordered_map>
#include <functional>
#include <locale>
#include <codecvt>

class SVGDocuments; // Forwarding Declaration

// Factory for creating SVG elements
class SVGElementFactory {
public:
    virtual std::unique_ptr<SVGElements> createElement(rapidxml::xml_node<>* node) const = 0;
    virtual ~SVGElementFactory() = default;
};

// Factory for creating rectangles
class RectFactory : public SVGElementFactory {
public:
    std::unique_ptr<SVGElements> createElement(rapidxml::xml_node<>* node) const override;
};

// Factory for creating circles
class CircleFactory : public SVGElementFactory {
public:
    std::unique_ptr<SVGElements> createElement(rapidxml::xml_node<>* node) const override;
};

// Factory for creating ellipses
class EllipseFactory : public SVGElementFactory {
public:
    std::unique_ptr<SVGElements> createElement(rapidxml::xml_node<>* node) const override;
};

// Factory for creating lines
class LineFactory : public SVGElementFactory {
public:
    std::unique_ptr<SVGElements> createElement(rapidxml::xml_node<>* node) const override;
};

// Factory for creating paths
class PathFactory : public SVGElementFactory {
public:
    std::unique_ptr<SVGElements> createElement(rapidxml::xml_node<>* node) const override;
};

// Factory for creating polygons
class PolygonFactory : public SVGElementFactory {
public:
    std::unique_ptr<SVGElements> createElement(rapidxml::xml_node<>* node) const override;
};

// Factory for creating polylines
class PolylineFactory : public SVGElementFactory {
public:
    std::unique_ptr<SVGElements> createElement(rapidxml::xml_node<>* node) const override;
};

// Factory for creating texts
class TextFactory : public SVGElementFactory {
public:
    std::unique_ptr<SVGElements> createElement(rapidxml::xml_node<>* node) const override;
};

class GroupFactory : public SVGElementFactory {
public:
    std::unique_ptr<SVGElements> createElement(rapidxml::xml_node<>* node) const override;
};

// Registry for SVG element factories
class SVGFactoryRegistry {
private:
    std::unordered_map<std::string, std::function<std::unique_ptr<SVGElements>(rapidxml::xml_node<>*)>> factoryMap;

public:
    void registerFactory(const std::string& name, std::function<std::unique_ptr<SVGElements>(rapidxml::xml_node<>*)> factory);
    std::unique_ptr<SVGElements> createElementFromFactory(const std::string& name, rapidxml::xml_node<>* node);
};

class SVGFactoryRegistrar {
public:
    template<class FactoryType>
    void registerFactories(SVGFactoryRegistry& registry, const std::string& factoryName) {
        registry.registerFactory(factoryName, [](rapidxml::xml_node<>* node) {
            FactoryType factory;

            return factory.createElement(node);
        });
    }

    void registerFactories(SVGFactoryRegistry& registry);
};

#endif // FACTORY_H