#include "camera.hpp"

Camera::Camera():
  name_ {"Default Camera"},
  fovX_ {60.0f},
  eye_ {0.1f, 0.0f, 1.0f},
  dir_ {0.0f, 0.0f, -1.0f},
  up_ {0.0f, 1.0f, 0.0f} {}


Camera::Camera(std::string const& name, float fovX):
  name_ {name},
  fovX_ {fovX},
  eye_ {0.1f, 0.0f, 1.0f},
  dir_ {0.0f, 0.0f, -1.0f},
  up_ {0.0f, 1.0f, 0.0f} {}

Camera::~Camera() {

}

Ray Camera::compRay(int x, int y, int width, int height){

  float dx = float(x) * 1.0/float(width) - 0.5;
  float dy = float(y) * 1.0 /float(height) - 0.5;
  float dz = -1.0 * (0.5/(tan(fovX_/2)));

  Ray ray {eye_, glm::vec3{dx, dy, dz}};
  auto mat = transform();

  glm::vec4 v1 {ray.origin_, 1.0f};
  glm::vec4 v2 {ray.direction_, 0.0f};

  glm::vec3 v3 {mat * v1};
  glm::vec3 v4 {mat * v2};

  return Ray{v3, v4};
}

glm::mat4 Camera::transform(){

  glm::vec3 n = glm::normalize(dir_);
  glm::vec3 e = eye_;

  glm::vec3 u = glm::normalize(glm::cross(n, up_));
  glm::vec3 v = glm::normalize(glm::cross(u, n));

  glm::mat4 transCam;
  transCam[0] = glm::vec4{u, 0.0f};
  transCam[1] = glm::vec4{v, 0.0f};
  transCam[2] = glm::vec4{-1.0f * n, 0.0f};
  transCam[3] = glm::vec4{e, 1.0f};

  return transCam;
}

// std::ostream& operator<<(std::ostream& os, Camera const& cam){
//   os<<"Name der Kamera: " << cam.name_<<std::endl<<
//     "Öffnungswinkel: "<<cam.fovX_<<std::endl<<
//     "Eye: ("<<cam.eye_.x<<", "<<cam.eye_.y<<", "<<cam.eye_.z<<")"<<std::endl<<
//     "Direction: ("<<cam.dir_.x<<", "<<cam.dir_.y<<", "<<cam.dir_.z<<")"<<std::endl<<
//     "Up: ("<<cam.up_.x<<", "<<cam.up_.y<<", "<<cam.up_.z<<")"std::endl;
//     return os;
//}
