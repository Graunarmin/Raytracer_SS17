#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "shape.hpp"
class Shape;

class Composite : public Shape{

  Composite();
  Composite(std::string const& name);
  ~Composite();

  float area() const override;
  float volume() const override;
  OptionalHit intersect(Ray const& ray, float& t) override;

  std::ostream& print(std::ostream& os) const override;
  glm::vec3 computeNorm(OptionalHit const& hit) const override;

  //Member:
  std::string name_;
  std::vector<std::shared_ptr<Shape>> shapes_;

};

#endif //COMPOSITE_HPP
