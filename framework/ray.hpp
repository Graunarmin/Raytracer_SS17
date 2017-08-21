#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>


struct Ray{

  //define shape box Wuerfel 100 10 -300 180 70 -350 blue
  //(define shape sphere Kugel1 -200 0 -350 150 blue

  Ray():
    origin_{},
    direction_{}{}

  //normalized direction in constructor!
  Ray(glm::vec3 const& origin, glm::vec3 const& direction):
    origin_{origin},
    direction_{glm::normalize(direction)}{}

  friend std::ostream& operator<<(std::ostream&os, Ray const& ray){
    os<<"Ray origin: (" << ray.origin_.x << ", "<<ray.origin_.y<<", "<<
        ray.origin_.y<<"), direction: ("<<ray.direction_.x<<", "<<
        ray.direction_.y<<", "<<ray.direction_.z<<")\n";
    return os;
  }

  glm::vec3 origin_;
  glm::vec3 direction_;
  //glm::vec3 distance_; //Strahlenparameter t?

};
#endif //RAY_HPP
