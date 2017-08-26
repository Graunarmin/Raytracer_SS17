#include "camera.hpp"

Camera::Camera(){
  name_{"Default Camera"},
  fovX_ {0.0f},
  eye_ {0.0f, 0.0f, 0.0f},
  dir_ {0.0f, 0.0f, 0.0f},
  up_ {0.0f, 0.0f, 0.0f},
}

Camera::Camera(std::string name, float fovX, glm::vec3 eye, glm::vec3 dir, glm::vec3 up):
  name_{name},
  fovX_{fovX},
  eye_{eye},
  dir_{dir},
  up_{up}{}

Camera::~Camera() {}
