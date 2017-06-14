#include "box.hpp"

//Konstruktoren
Box::Box():
  min_{-1},
  max_{1}/*,
  name_{"box"},
  color_{1.0f, 1.0f, 1.0f}*/{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max/*,
        std::string const& name, Color const& color*/):
  min_{min},
  max_{max}/*,
  name_{name},
  color_{color}*/{}


//Methoden

glm::vec3 const& Box::getMin() const{
  return min_;
}

glm::vec3 const& Box::getMax() const{
  return max_;
}

float Box::area() const{
  float a = std::abs(max_.x - min_.x);
  float b = std::abs(max_.y - min_.y);
  float c = std::abs(max_.z - min_.z);

  return 2*((a*b) + (b*c) + (a*c));
}

float Box::volume() const{
  float a = std::abs(max_.x - min_.x);
  float b = std::abs(max_.y - min_.y);
  float c = std::abs(max_.z - min_.z);
  return a*b*c;

}
