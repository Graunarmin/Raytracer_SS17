#include "shape.hpp"

Shape::Shape():
  name_{"Cooles Objekt"},
  color_{1.0f, 1.0f, 1.0f}{
    std::cout << "Default Constructor Base class Shape\n";
  }

Shape::Shape(std::string const& name, Color const& color):
  name_{name},
  color_{color}{
    std::cout << "Constructor Base class Shape\n";
  }

  Shape::~Shape()
  {
    std::cout << "Deconstructor Base class Shape\n";
  }

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
