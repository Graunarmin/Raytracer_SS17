#include "sphere.hpp"

//Konstruktoren
Sphere::Sphere():
  Shape{},
  center_{0.0f, 0.0f, 0.0f},
  radius_{1.0f}{
    std::cout << "Default Constructor derived class Sphere\n";
  }

Sphere::Sphere(glm::vec3 const& center, float radius,
              std::string const& name, Material const& material):
  Shape{name, material},
  center_{center},
  radius_{radius}{
    std::cout << "Constructor derived class Sphere\n";
  }

Sphere::~Sphere(){
  std::cout << "Deconstructor derived class Sphere\n";
}

glm::vec3 const& Sphere::getCenter() const{
  return center_;
}

float Sphere::getRadius() const{
  return radius_;
}

float Sphere::area() const{
  return 4.0 * M_PI * radius_ * radius_;
}

float Sphere::volume() const{
  return ((4.0 * M_PI * pow(radius_, 3.0))/3.0);
}

std::ostream& Sphere::print(std::ostream& os) const{
  //erst Name und Color, dann das Sphere-spezifische
  Shape::print(os);
  os << "Center: " << "(" << center_.x << "," << center_.y << "," << center_.z << "),\n"
  << "Radius: " << radius_ << "\n" << "\n";
  return os;
}

bool Sphere::intersect(Ray const& ray, float& distance) const{
  //distance ist dann der Abstand vom ray.origin zum nächsten Punkt der Kugel
  //bekommt nen Ray und ne "leere" distance, wird auf sphere aufgerufen
  return glm::intersectRaySphere(ray.origin_, ray.direction_,
          center_, radius_*radius_, distance);
}
