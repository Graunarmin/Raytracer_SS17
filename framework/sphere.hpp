#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"


class Sphere : public Shape{

public:

  //Konstruktoren
  Sphere();
  Sphere(glm::vec3 const& center, float radius,
          std::string const& name, Color const& color);
  Sphere(glm::vec3 const& center, float radius,
          std::string const& name, Material const& material);

  ~Sphere() override;

  //Methoden
  glm::vec3 const& getCenter() const;
  float getRadius() const;

  //override Methoden
  float area() const override;
  float volume() const override;

  std::ostream& print(std::ostream& os) const override;
  OptionalHit intersect(Ray const& ray, float& t) const override;
  glm::vec3 computeNorm(OptionalHit const& hit) const override;
  void transform() override;
  void toScene(std::ofstream& file) const override;

private:

  glm::vec3 center_;
  float radius_;

};
#endif //SPHERE_HPP
