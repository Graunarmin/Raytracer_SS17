#include "sphere.hpp"

//Konstruktoren
Sphere::Sphere():
  Shape{},
  center_{0.0f, 0.0f, 0.0f},
  radius_{0.0f}{}

Sphere::Sphere(glm::vec3 const& center, float radius,
          std::string const& name, Color const& color):
  Shape{name, color},
  center_{center},
  radius_{radius}{}


Sphere::Sphere(glm::vec3 const& center, float radius,
              std::string const& name, Material const& material):
  Shape{name, material},
  center_{center},
  radius_{radius}{}

Sphere::~Sphere(){
  //std::cout << "Deconstructor derived class Sphere\n";
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

OptionalHit Sphere::intersect(Ray const& ray, float& t) {
  //distance ist dann der Abstand vom ray.origin zum nächsten Punkt der Kugel
  //bekommt nen Ray und ne "leere" distance, wird auf sphere aufgerufen
  glm::vec3 intP{0.0f};
  auto hit = glm::intersectRaySphere(ray.origin_, ray.direction_,
          center_, radius_*radius_, t);
  if(hit){
    //Wenn es einen SP gibt: Koordinaten bestimmen
    intP.x = ray.origin_.x + (t*ray.direction_.x);
    intP.y = ray.origin_.y + (t*ray.direction_.y);
    intP.z = ray.origin_.z + (t*ray.direction_.z);
  }
  return OptionalHit{hit, t, intP};
}

glm::vec3 Sphere::computeNorm(OptionalHit const& hit) const{
   return glm::normalize(hit.intersectionPoint_ - getCenter());
}

std::shared_ptr<Shape> Sphere::transform(){
  glm::vec4 c{center_.x, center_.y, center_.z, 1.0f};
  glm::vec3 h{c * world_transformation_};
  center_ = h;
  return std::shared_ptr<Sphere>(this);
}
