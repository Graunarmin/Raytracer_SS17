#include "box.hpp"

//Konstruktoren
Box::Box():
  Shape{},
  min_{-1},
  max_{1}{
    std::cout << "Default Constructor derived class Box\n";
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
    std::cout << "Constructor derived class Box\n";
  }

Box::~Box(){
  std::cout << "Deconstructor derived class Box\n";
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

}

std::ostream& Box::print(std::ostream& os) const{
  //printet erst den Shape-Teil (Name und Farbe)
  Shape::print(os);
  //danach werden die anderen Werte in os gespeichert und über << ausgegeben
  os << "Min: " << "(" << min_.x << "," << min_.y << "," << min_.z << ")\n"
  << "Max: " << "(" << max_.x << "," << max_.y << "," << max_.z << ")\n" << "\n" ;
  return os;
}
