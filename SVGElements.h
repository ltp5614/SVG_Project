#ifndef SVGELEMENTS_H
#define SVGELEMENTS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

class SVGElements {
public:
    virtual void render() const = 0;
    virtual ~SVGElements() = default;
};

#endif // SVGELEMENTS_H