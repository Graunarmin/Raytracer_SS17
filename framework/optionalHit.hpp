#ifndef OPTIONALHIT_HPP
#define OPTIONALHIT_HPP

#include <iostream>
#include <glm/vec3.hpp>
#include <cmath>

class Shape;

struct OptionalHit{

  OptionalHit():
    hit_{false},
    t_{0.0f},
    intersectionPoint_{0.0f},
    nearestShape_{nullptr}{}

  OptionalHit(bool hit, float distance, glm::vec3 const& intP):
      hit_{hit},
      t_{distance},
      intersectionPoint_{intP},
      nearestShape_{nullptr}{}

  OptionalHit(bool hit, float distance, glm::vec3 const& intP, std::shared_ptr<Shape> const& s):
      hit_{hit},
      t_{distance},
      intersectionPoint_{intP},
      nearestShape_{s}{}

  bool hit_;
  float t_;
  glm::vec3 intersectionPoint_;
  std::shared_ptr<Shape> nearestShape_;
  //Jetzt können wir Pointer auf Objekte im hit speichern!

};

#endif //OPTIONALHIT_HPP
