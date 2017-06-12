#include "box.hpp"

//Konstruktoren
Box():
  m_min{-1},
  m_max{1}{}

Box(glm::vec3 const& min, glm::vec3 const& max):
  m_min{min},
  m_max{max}{}


//Methoden

glm::vec3 const& getMin() const{
  return m_min;
}

glm::vec3 const& getMax() const{
  return m_max;
}

float area() const override{
  float a = std::abs(std::abs(m_max.x) - std::abs(m_min.x));
  float b = std::abs(std::abs(m_max.y) - std::abs(m_min.y));
  float c = std::abs(std::abs(m_max.z) - std::abs(m_min.z));

  return 2*((a*b) + (b*c) + (a*c));
}

float volume() const override{
  float a = std::abs(std::abs(m_max.x) - std::abs(m_min.x));
  float b = std::abs(std::abs(m_max.y) - std::abs(m_min.y));
  float c = std::abs(std::abs(m_max.z) - std::abs(m_min.z));

  return a*b*c;

}
