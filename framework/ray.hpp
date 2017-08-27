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

  friend std::ostream& operator<<(std::ostream&os, Ray const& ray){
    os<<"Ray origin: (" << ray.origin_.x << ", "<<ray.origin_.y<<", "<<
        ray.origin_.y<<"), direction: ("<<ray.direction_.x<<", "<<
        ray.direction_.y<<", "<<ray.direction_.z<<")\n";
    return os;
  }

  Ray transformRay(glm::mat4 const& mat){

    glm::vec4 v1 {origin_, 1.0f};
    glm::vec4 v2 {direction_, 0.0f};

    glm::vec3 v3 {mat * v1};
    glm::vec3 v4 {mat * v2};

    return Ray{v3, v4};

  }

  glm::vec3 origin_;
  glm::vec3 direction_;

};
#endif //RAY_HPP
