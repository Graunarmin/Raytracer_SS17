#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Shape.hpp"


class Sphere : public Shape{

public:

  Sphere();
  Sphere(glm::vec3 const&y center, float radius);

  glm::vec3 const& getCenter() const;
  float getRadius() const;

  float area() const override;
  float volume() const override;

private:
  glm::vec3 m_center;
  float m_radius;


};
#endif //SPHERE_HPP
