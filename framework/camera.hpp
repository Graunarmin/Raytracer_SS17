#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera{

  Camera():
  Camera(std::string name, float fovX, glm::vec3 eye, glm::vec3 dir, glm::vec3 up):
  ~Camera():

  //member
private:
  std::string name_;
  glm::vec3 fovX;
  glm::vec3 eye_;
  glm::vec3 dir_;
  glm::vec3 up_;
}
