#include "sphere.hpp"

//Konstruktoren
Sphere::Sphere():
  Shape{},
  center_{0.0f, 0.0f, 0.0f},
  radius_{1.0f}{}

Sphere::Sphere(glm::vec3 const& center, float radius,
              std::string const& name, Color const& color):
  Shape{name, color},
  center_{center},
  radius_{radius}{}

glm::vec3 const& Sphere::getCenter() const{
  return center_;
}

float Sphere::getRadius() const{
  return radius_;
}

float Sphere::area() const{
  return 4.0 * M_PI * radius_ * radius_;
}

float Sphere::volume() const{
  return ((4.0 * M_PI * pow(radius_, 3.0))/3.0);
}

std::string Sphere::getName() const{
  return name_;
}

Color Sphere::getColor() const{
  return color_;
}
