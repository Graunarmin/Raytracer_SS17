#ifndef OPTIONALHIT_HPP
#define OPTIONALHIT_HPP

//#include "shape.hpp"

#include <iostream>
#include <glm/vec3.hpp>
#include <cmath>
//#include <memory>

class Shape;

struct OptionalHit{

  OptionalHit():
    hit_{false},
    t_{0.0f},
    intersectionPoint_{0.0f},
    nearestShape_{nullptr}{}

  OptionalHit(bool hit, float distance, glm::vec3 intP):
      hit_{hit},
      t_{distance},
      intersectionPoint_{intP},
      nearestShape_{nullptr}{}

  OptionalHit(bool hit, float distance, glm::vec3 intP, std::shared_ptr<Shape> const& s):
      hit_{hit},
      t_{distance},
      intersectionPoint_{intP},
      nearestShape_{s}{}

  bool hit_;
  float t_;
  glm::vec3 intersectionPoint_;
  std::shared_ptr<Shape> nearestShape_;
  //Jetzt können wir die Objekte direkt im hit speichern!
  //Also theoretisch. Praktisch leider nicht.

};

#endif //OPTIONALHIT_HPP
