#ifndef SVGELEMENTS_H
#define SVGELEMENTS_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <string>
#include <windows.h>
#include <gdiplus.h>
#include "rapidxml.hpp"
#include "Color.h"
#include "Transform.h"

#pragma comment (lib,"Gdiplus.lib")


class SVGElements {
  protected:
      std::string fill;
      std::string stroke;
      float fill_opacity;
      float stroke_width;
      float stroke_opacity;
      Transform transform;
      
  public:
      SVGElements(const std::string& fill, const std::string& stroke,
                  float fill_opacity, float stroke_width, float stroke_opacity,
                  Transform transform);

      virtual void render(Gdiplus::Graphics& graphics, Gdiplus::Matrix& matrix) const = 0; // Phương thức render ảo
      virtual PointSVG getCenter() const = 0; // Phương thức lấy tâm ảo

      // Getter và Setter
      std::string getFill() const;
      void setFill(const std::string& value);

      float getFillOpacity() const;
      void setFillOpacity(float value);

      std::string getStroke() const;
      void setStroke(const std::string& value);

      float getStrokeWidth() const;
      void setStrokeWidth(float value);

      float getStrokeOpacity() const;
      void setStrokeOpacity(float value);

      Transform getTransform() const;
      void setTransform(const Transform& value);

      void applyAttributes(const std::string& fill, float fill_opacity,
						   const std::string& stroke, float stroke_width,
						   float stroke_opacity, Transform transform);

      virtual ~SVGElements() = default;
};

#endif // SVGELEMENTS_H
