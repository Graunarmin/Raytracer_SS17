#include "shape.hpp"

Shape::Shape():
  name_{"Cooles Objekt"},
  color_{1.0f, 1.0f, 1.0f}{}

Shape::Shape(std::string const& name, Color const& color):
  name_{name},
  color_{color}{}
