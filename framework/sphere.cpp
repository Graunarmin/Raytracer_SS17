#include "sphere.hpp"

//Konstruktoren
Sphere::Sphere():
  center_{0.0f, 0.0f, 0.0f},
  radius_{1.0f}/*,
  name_{"Sphere"},
  /* color_{1.0f, 1.0f, 1.0f}*/{}

Sphere::Sphere(glm::vec3 const& center, float radius/*,
              std::string const& name, Color const& color*/):
  center_{center},
  radius_{radius}/*,
  name_{name},
  color_{color}*/{}

glm::vec3 const& Sphere::getCenter() const{
  return center_;
}

float Sphere::getRadius() const{
  return radius_;
}

float Sphere::area() const{
  return 4 * M_PI * pow(radius_, 2);
}

float Sphere::volume() const{
  return ((4 * M_PI * pow(radius_, 3))/3);
}
