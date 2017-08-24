#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"


class Sphere : public Shape{

public:

  Sphere();
  Sphere(glm::vec3 const& center, float radius,
          std::string const& name, Color const& color);
  Sphere(glm::vec3 const& center, float radius,
          std::string const& name, Material const& material);


  ~Sphere() override;

  glm::vec3 const& getCenter() const;
  float getRadius() const;

  float area() const override;
  float volume() const override;

  std::ostream& print(std::ostream& os) const override;

  OptionalHit intersect(Ray const& ray, float& t) override;
  glm::vec3 computeNorm(OptionalHit const& hit) const override;

  //std::shared_ptr<Sphere> createPointer() const override;


private:
  glm::vec3 center_;
  float radius_;

};
#endif //SPHERE_HPP
