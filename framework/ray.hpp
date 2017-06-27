#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>


struct Ray{

  Ray():
    origin_{},
    direction_{}{}

  //normalized direction in constructor!
  Ray(glm::vec3 const& origin, glm::vec3 const& direction):
    origin_{origin},
    direction_{glm::normalize(direction)}{}

  glm::vec3 const& getOrigin() const{
    return origin_;
  }

  glm::vec3 const& getDirection() const{
    return direction_;
  }

  glm::vec3 origin_;
  glm::vec3 direction_;
  //glm::vec3 distance_; //Strahlenparameter t?

};
#endif //RAY_HPP
