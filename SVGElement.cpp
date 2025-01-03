﻿#include "SVGElements.h"

SVGElements::SVGElements(const std::string& fill, const std::string& stroke, 
                         float fill_opacity, float stroke_width, float stroke_opacity,
                         Transform transform) 
           : fill(fill), stroke(stroke), 
             fill_opacity(fill_opacity), stroke_width(stroke_width), stroke_opacity(stroke_opacity), 
             transform(transform) { 

    if (fill != "none" && fill_opacity == 0) {
        this->fill_opacity = 1;
    }
    
    if (stroke != "none" && stroke_opacity == 0) {
        this->stroke_opacity = 1;
    }

    if (stroke != "none" && stroke_width == 0) {
        this->stroke_width = 1;
    }
}

// Getter và Setter
std::string SVGElements::getFill() const { return fill; }
void SVGElements::setFill(const std::string& value) { fill = value; }

float SVGElements::getFillOpacity() const { return fill_opacity; }
void SVGElements::setFillOpacity(float value) { fill_opacity = value; }

std::string SVGElements::getStroke() const { return stroke; }
void SVGElements::setStroke(const std::string& value) { stroke = value; }

float SVGElements::getStrokeWidth() const { return stroke_width; }
void SVGElements::setStrokeWidth(float value) { stroke_width = value; }

float SVGElements::getStrokeOpacity() const { return stroke_opacity; }
void SVGElements::SVGElements::setStrokeOpacity(float value) { stroke_opacity = value; }

Transform SVGElements::getTransform() const { return transform; }

void SVGElements::setTransform(const Transform& value) {
  if(transform.getRotationAngle() == 0) {
    transform.setRotationAngle(value.getRotationAngle());
  }

  if(transform.getTranslateX() == 0 && transform.getTranslateY() == 0) {
    transform.setTranslateX(value.getTranslateX());
    transform.setTranslateY(value.getTranslateY());
  }

  if(transform.getScaleX() == 1 && transform.getScaleY() == 1) {
    transform.setScaleX(value.getScaleX());
    transform.setScaleY(value.getScaleY());
  }
}

void SVGElements::applyAttributes(const std::string& fill, float fill_opacity,
                                  const std::string& stroke, float stroke_width,
                                  float stroke_opacity, Transform transform) {
    // Chỉ thay đổi fill nếu giá trị mới không phải là "none"
    if (fill != "none" && this->fill == "none") {
        setFill(fill);
    }
    
    // Chỉ thay đổi fill_opacity nếu giá trị mới hợp lệ (khác giá trị mặc định)
    if (fill_opacity != 0.0f && (this->fill_opacity == 1.0f || this->fill_opacity == 0.0f)) {
        setFillOpacity(fill_opacity);
    }
    else if(fill_opacity == 0 && fill != "none")
    {
        setFillOpacity(1);
    }

    if(stroke != "none" && this->stroke_width == 0 && stroke_width == 0)
    {
        setStrokeWidth(1);
    }
    
    // Chỉ thay đổi stroke nếu giá trị mới không phải là "none"
    if (stroke != "none" && this->stroke == "none") {
        setStroke(stroke);
    }
    
    // Chỉ thay đổi stroke_width nếu giá trị mới lớn hơn 0
    if (stroke_width > 0.0f && this->stroke_width == 0.0f) {
        setStrokeWidth(stroke_width);
    }
    
    // Chỉ thay đổi stroke_opacity nếu giá trị mới hợp lệ (khác giá trị mặc định)
    if (stroke_opacity != 0.0f && (this->stroke_opacity == 1.0f || this->stroke_opacity == 0.0f)) {
        setStrokeOpacity(stroke_opacity);
    }
    else if(stroke_opacity == 0 && stroke != "none")
    {
        setStrokeOpacity(1);
    }
}
