#include "sphere.hpp"

//Konstruktoren
Sphere::Sphere():
  m_center{0.0f, 0.0f, 0.0f},
  m_radius{1.0f}{}

Sphere::Sphere(glm::vec3 const& center, float radius):
  m_center{center},
  m_radius{radius}{}

glm::vec3 const& Sphere::getCenter() const{
  return m_center;
}

float Sphere::getRadius() const{
  return m_radius;
}

float Sphere::area() const{
  return 4 * M_PI * pow(m_radius, 2);
}

float Sphere::volume() const{
  return (4/3)* M_PI * pow(m_radius, 3);
}
