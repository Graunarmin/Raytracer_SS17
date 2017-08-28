#include "box.hpp"

//Konstruktoren
Box::Box():
  Shape{},
  min_{0.0f},
  max_{0.0f}{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
          std::string const& name, Color const& color):
    Shape{name, color},
    min_{min},
    max_{max}{
      /*min_.x = std::min(min.x, max.x);
      min_.y = std::min(min.y, max.y);
      min_.z = std::min(min.z, max.z);
      max_.x = std::max(min.x, max.x);
      max_.y = std::max(min.y, max.y);
      max_.z = std::max(min.z, max.z);*/
    }

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
        std::string const& name, Material const& material):
  Shape{name, material},
  min_{min},
  max_{max}{
    /*min_.x = std::min(min.x, max.x);
    min_.y = std::min(min.y, max.y);
    min_.z = std::min(min.z, max.z);
    max_.x = std::max(min.x, max.x);
    max_.y = std::max(min.y, max.y);
    max_.z = std::max(min.z, max.z);*/
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

OptionalHit Box::intersect(Ray const& ray, float& t){

  glm::vec3 intP{0.0f};

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
    //t = std::abs(tF);
    return OptionalHit{false, 0, intP};
  }

  float tFar = std::min(tF, tFZ);
  float tNear = std::max(tN, tNZ);

  //Bedingungen!!
  if((tFar < 0) || (tFar < tNear) || (tNear < 0)){
    //t = std::abs(tFar);
    return OptionalHit{false, 0, intP};
  }

  t = std::abs(tNear);
  //Schnittpunkt berechnen
  intP.x = ray.origin_.x + (t*ray.direction_.x);
  intP.y = ray.origin_.y + (t*ray.direction_.y);
  intP.z = ray.origin_.z + (t*ray.direction_.z);

  return OptionalHit{true, t, intP};
}

std::ostream& Box::print(std::ostream& os) const{
  //printet erst den Shape-Teil (Name und Farbe)
  Shape::print(os);
  //danach werden die anderen Werte in os gespeichert und über << ausgegeben
  os << "Min: " << "(" << min_.x << "," << min_.y << "," << min_.z << ")\n"
  << "Max: " << "(" << max_.x << "," << max_.y << "," << max_.z << ")\n" << "\n" ;
  return os;
}

glm::vec3 Box::computeNorm(OptionalHit const& hit) const{
  if((hit.intersectionPoint_.x == Approx(min_.x))){   //Dann yz Ebene n = (0,1,1)
    return glm::normalize(glm::vec3{-1.0f, 0.0f, 0.0f});
  }
  else if((hit.intersectionPoint_.x == Approx(max_.x))){
    return glm::normalize(glm::vec3{1.0f, 0.0f, 0.0f});
  }
  else if((hit.intersectionPoint_.y == Approx(min_.y))){   //Dann xz Ebene n = (1,0,1)
    return glm::normalize(glm::vec3{0.0f, -1.0f, 0.0f});
  }
  else if((hit.intersectionPoint_.y == Approx(max_.y))){
    return glm::normalize(glm::vec3{0.0f, 1.0f, 0.0f});
  }
  else if((hit.intersectionPoint_.z == Approx(min_.z))){   //Dann xy Ebene n = (1,1,0)
    return glm::normalize(glm::vec3{0.0f, 0.0f, -1.0f});
  }
  else if((hit.intersectionPoint_.z == Approx(max_.z))){
    return glm::normalize(glm::vec3{0.0f, 0.0f, 1.0f});
  }
  else{
     return glm::vec3{};
  }
}

std::shared_ptr<Shape> Box::transform(){
  std::cout<<"-------Box vorher: "<< *this;
  glm::vec4 mi{min_.x, min_.y, min_.z, 1.0f};
  glm::vec4 ma{max_.x, max_.y, max_.z, 1.0f};

  glm::vec3 j{mi * world_transformation_};
  glm::vec3 i{ma * world_transformation_};

  min_ = j;
  max_ = i;
  std::cout<<"-------Box nachher: "<< *this;

  return std::shared_ptr<Box>(this);
}
