#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include "ray.hpp"

class Camera{

 public:

  Camera();
  Camera(std::string const& name, float fovX);
  Camera(std::string const& name, float fovX, glm::vec3 eye, glm::vec3 dir);
  ~Camera();

  Ray compRay(int x, int y, int width, int height);

  glm::mat4 transform();
  void around();
  void toScene(std::ofstream& file);
  //member

  std::string name_;
  float fovX_;
  glm::vec3 eye_;
  glm::vec3 dir_;
  glm::vec3 up_;

  //Member zum Umkreisen:
  float angle_; //noch in Bogenmaß umrechnen!
  glm::vec3 sceneCenter_;
  float circleRadius_;
};

#endif //CAMERA_HPP
