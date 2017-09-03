#ifndef BOX_HPP
#define BOX_HPP
#include "shape.hpp"
#include <catch.hpp>


class Box : public Shape{

public:

  //Konstruktoren
  Box();
  Box(glm::vec3 const& min, glm::vec3 const& max,
      std::string const& name, Color const& color);
  Box(glm::vec3 const& min, glm::vec3 const& max,
      std::string const& name, Material const& material);

  ~Box() override;

  //Methoden
  glm::vec3 const& getMin() const;
  glm::vec3 const& getMax() const;

  //Override Methoden
  float area() const override;
  float volume() const override;

  OptionalHit intersect(Ray const& ray, float& t) const override;
  std::ostream& print(std::ostream& os) const override;
  glm::vec3 computeNorm(OptionalHit const& hit) const override;
  void transform() override;
  void toScene(std::ofstream& file) const override;

private:

  //Raumdiagonale zwischen min und max
  glm::vec3 min_;
  glm::vec3 max_;

};

#endif //BOX_HPP
