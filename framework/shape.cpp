#include "shape.hpp"

Shape::Shape():
  name_{"Cooles Objekt"},
  color_{1.0f, 1.0f, 1.0f}{}

Shape::Shape(std::string const& name, Color const& color):
  name_{name},
  color_{color}{}

  // Shape::~Shape()
  // {
  //   delete->this;
  // }

  std::string Shape::getName() const{
    return name_;
  }

  Color Shape::getColor() const{
    return color_;
  }

  std::ostream& Shape::print(std::ostream& os) const{
    os << "Name: " << name_ << " \nRGB: " << color_ ;
    return os;
  }

  std::ostream& operator<<(std::ostream& os, Shape const& s){
    return s.print(os);
  }
