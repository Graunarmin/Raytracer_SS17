#ifndef BOX_HPP
#define BOX_HPP

#include "Shape.hpp"

class Box : public Shape{

public:

  Box();
  Box(glm::vec3 const& min, glm::vec3 const& max);

  glm::vec3 const& getMin() const;
  glm::vec3 const& getMax() const;

  float area() const override;
  float volume() const override;

private:
  glm::vec3 m_min;
  glm::vec3 m_max;


};

#endif //BOX_HPP
