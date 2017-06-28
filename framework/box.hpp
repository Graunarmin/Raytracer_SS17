#ifndef BOX_HPP
#define BOX_HPP
#include "shape.hpp"

class Box : public Shape{

public:

  Box();
  Box(glm::vec3 const& min, glm::vec3 const& max,
      std::string const& name, Color const& color);
  Box(glm::vec3 const& min, glm::vec3 const& max,
      std::string const& name, Material const& material);

  ~Box() override;

  glm::vec3 const& getMin() const;
  glm::vec3 const& getMax() const;

  float area() const override;
  float volume() const override;
  // bool intersect(Ray const& ray, float& t) override;

  std::ostream& print(std::ostream& os) const override;

private:
  //Raumdiagonale zwischen min und max
  glm::vec3 min_;
  glm::vec3 max_;

};

#endif //BOX_HPP
