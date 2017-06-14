#include "box.hpp"

//Konstruktoren
Box::Box():
  Shape{},
  min_{-1},
  max_{1}{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
        std::string const& name, Color const& color):
  Shape{name, color},
  min_{min},
  max_{max}{}


//Methoden
glm::vec3 const& Box::getMin() const{
  return min_;
}

glm::vec3 const& Box::getMax() const{
  return max_;
}

float Box::area() const{
  auto diff = max_ - min_;
  return 2*((diff.x*diff.y) + (diff.y*diff.z) + (diff.x*diff.z));
}

float Box::volume() const{
  auto diff = max_ - min_;
  return diff.x*diff.y*diff.z;
}