#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include "ray.hpp"

class Camera{

 public: 

  Camera();
  Camera(std::string name, float fovX);
  ~Camera();

  Ray compRay(int x, int y, int width, int height);

  glm::mat4 transform();

  //member

  std::string name_;
  float fovX_;
  glm::vec3 eye_;
  glm::vec3 dir_;
  glm::vec3 up_;
};

#endif