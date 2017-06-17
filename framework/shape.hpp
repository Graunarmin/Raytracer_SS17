#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"
#include "ray.hpp"

#include <glm/vec3.hpp>
#include <cmath>
#include <iostream>
#include <string>

class Shape{

public:
  Shape();
  Shape(std::string const& name, Color const& color);

  // virtual ~Shape();


  virtual float area() const = 0;
  virtual float volume() const = 0;

  std::string getName() const;
  Color getColor() const;

  virtual std::ostream& print(std::ostream& os) const;

protected:
  std::string name_;
  Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif //SHAPE_HPP
