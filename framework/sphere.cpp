#include "sphere.hpp"

//Konstruktoren
Sphere():
  m_center{0},
  m_radius{1.0f}{}

Sphere(glm::vec3 const& center, float radius):
  m_center{center},
  m_radius{radius}{}

glm::vec3 const& getCenter() const{
  return m_center;
}

float getRadius() const{
  return m_radius;
}

float area() const override;
float volume() const override;
