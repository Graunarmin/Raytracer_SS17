#include "sphere.hpp"

//Konstruktoren
Sphere::Sphere():
  Shape{},
  center_{0.0f, 0.0f, 0.0f},
  radius_{1.0f}{}

Sphere::Sphere(glm::vec3 const& center, float radius,
              std::string const& name, Color const& color):
  Shape{name, color},
  center_{center},
  radius_{radius}{}

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
  Shape::print(os);
  os << "Center: " << "(" << center_.x << "," << center_.y << "," << center_.z << "),\n"
  << "Radius: " << radius_ << "\n" << "\n";
  return os;
}

bool Sphere::intersect(Ray const& ray, float& distance) const{
  return glm::intersectRaySphere(ray.origin_, ray.direction_,
          center_, radius_*radius_, distance);
}
