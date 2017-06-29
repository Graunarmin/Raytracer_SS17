#include "box.hpp"

//Konstruktoren
Box::Box():
  Shape{},
  min_{-1},
  max_{1}{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
          std::string const& name, Color const& color):
    Shape{name, color},
    min_{min},
    max_{max}{
      min_.x = std::min(min.x, max.x);
      min_.y = std::min(min.y, max.y);
      min_.z = std::min(min.z, max.z);
      max_.x = std::max(min.x, max.x);
      max_.y = std::max(min.y, max.y);
      max_.z = std::max(min.z, max.z);
    }

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
        std::string const& name, Material const& material):
  Shape{name, material},
  min_{min},
  max_{max}{
    min_.x = std::min(min.x, max.x);
    min_.y = std::min(min.y, max.y);
    min_.z = std::min(min.z, max.z);
    max_.x = std::max(min.x, max.x);
    max_.y = std::max(min.y, max.y);
    max_.z = std::max(min.z, max.z);
  }

Box::~Box(){
  //std::cout << "Deconstructor derived class Box\n";
}

//Methoden
glm::vec3 const& Box::getMin() const{
  return min_;
}

glm::vec3 const& Box::getMax() const{
  return max_;
}

float Box::area() const{
  //2*(a*b + b*c + a*c)
  auto diff = max_ - min_;
  return 2*((diff.x * diff.y) + (diff.y * diff.z) + (diff.x * diff.z));
}

float Box::volume() const{
  //a*b*c
  auto diff = max_ - min_;
  return diff.x * diff.y * diff.z;
}

bool intersect(Ray const& ray, float& t){

  float tFarX;
  float tNearX;
  float tFarY;
  float tNearY;
  float tFar;
  float tNear;
  float tF;
  float tN;

  float tx1 = (min_.x - ray.origin_.x)/(ray.direction_.x);
  float tx2 = (max_.x - ray.origin_.x)/(ray.direction_.x);

  float ty1 = (min_.y - ray.origin_.y)/(ray.direction_.y);
  float ty2 = (max_.y - ray.origin_.y)/(ray.direction_.y);

  tFarX = std::max(tx1, tx2);
  tNearX = std::min(tx1, tx2);

  tFarY = std::max(ty1, ty2);
  tNearY = std::min(ty1, ty2);

  tFar = min(tFarX, tFarY);
  tNear = max(tNearX, tNearY);

  if(tNear < tFar){
    float tz1 = (min_.z - ray.origin_.z)/(ray.direction_.z);
    float tz2 = (max_.z - ray.origin_.z)/(ray.direction_.z);

    tFarZ = std::max(tz1, tz2);
    tNearZ = std::min(tz1, tz2);

    tF = std::min(tFarZ, tFar);
    tN = std::min(tNearZ, tNear);

    std::vec3 SP{};
  }
  else{
 //return kein SP
  }

}

std::ostream& Box::print(std::ostream& os) const{
  //printet erst den Shape-Teil (Name und Farbe)
  Shape::print(os);
  //danach werden die anderen Werte in os gespeichert und über << ausgegeben
  os << "Min: " << "(" << min_.x << "," << min_.y << "," << min_.z << ")\n"
  << "Max: " << "(" << max_.x << "," << max_.y << "," << max_.z << ")\n" << "\n" ;
  return os;
}
