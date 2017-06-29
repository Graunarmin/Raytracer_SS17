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

bool Box::intersect(Ray const& ray, float& t){

  float tx1 = (min_.x - ray.origin_.x)/(ray.direction_.x);
  float tx2 = (max_.x - ray.origin_.x)/(ray.direction_.x);

  float ty1 = (min_.y - ray.origin_.y)/(ray.direction_.y);
  float ty2 = (max_.y - ray.origin_.y)/(ray.direction_.y);

  float tz1 = (min_.z - ray.origin_.z)/(ray.direction_.z);
  float tz2 = (max_.z - ray.origin_.z)/(ray.direction_.z);

  float tFX = std::max(tx1, tx2);
  float tNX = std::min(tx1, tx2);

  float tFY = std::max(ty1, ty2);
  float tNY = std::min(ty1, ty2);

  float tFZ = std::max(tz1, tz2);
  float tNZ = std::min(tz1, tz2);

  float tF = std::min(tFX, tFY);
  float tN = std::max(tNX, tNY);

  if(tF < tN){
    t = tF;
    return false;
  }

  float tFar = std::min(tF, tFZ);
  float tNear = std::max(tN, tNZ);

  if((tFar < 0) || (tFar < tNear)){
    t = tFar;
    return false;
  }
  t = tNear;
  return true;

}

std::ostream& Box::print(std::ostream& os) const{
  //printet erst den Shape-Teil (Name und Farbe)
  Shape::print(os);
  //danach werden die anderen Werte in os gespeichert und über << ausgegeben
  os << "Min: " << "(" << min_.x << "," << min_.y << "," << min_.z << ")\n"
  << "Max: " << "(" << max_.x << "," << max_.y << "," << max_.z << ")\n" << "\n" ;
  return os;
}
