#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"

#include <glm/vec3.hpp>
#include <cmath>

class Shape{

public:
  // Shape();
  // Shape(std::string const& name, Color const& color);

  virtual float area() const = 0;
  virtual float volume() const = 0;
  // virtual std::string getName() const = 0;
  // virtual Color getColor() const = 0;

// protected:
//   std::string name_;
//   Color color_;
};

#endif //SHAPE_HPP
