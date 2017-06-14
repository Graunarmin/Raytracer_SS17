#ifndef BOX_HPP
#define BOX_HPP
#include "shape.hpp"

class Box : public Shape{

public:

  Box();
  Box(glm::vec3 const& min, glm::vec3 const& max/*,
      std::string const& name, Color const& color*/);

  glm::vec3 const& getMin() const;
  glm::vec3 const& getMax() const;

  float area() const override;
  float volume() const override;
  // std::string getName() const override;
  // Color getColor() const override;

private:
  glm::vec3 min_;
  glm::vec3 max_;
  // std::string name_;
  // Color color_;


};

#endif //BOX_HPP
