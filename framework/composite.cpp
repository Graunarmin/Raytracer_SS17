#include "composite.hpp"

Composite::Composite():
  name_{"Bestes Composite der Welt"},
  shapes_{}{}

Composite::Composite(std::string const& name):
  name_{name},
  shapes_{}{}

Composite::~Composite(){}

float Composite::area() const{
  std::cout<<"Sorry but a composite has no area.\n";
  return -1.0f;
}

float Composite::volume() const{
  std::cout << "Sorry, but a composite has no volume." << '\n';
  return -1.0f;
}

std::ostream& Composite::print(std::ostream& os) const{
  for(auto const& i: shapes_){
    i->print(os);
    os<<"\n";
  }
  return os;
}

OptionalHit Composite::intersect(Ray const& ray, float& t){

  OptionalHit nearestHit{false, std::numeric_limits<float>::max(), glm::vec3{0.0f}};

  for(auto const& i: shapes_){
    float distance = 0.0f;
    auto currentHit = i -> intersect(ray, distance);
    if(currentHit.hit_&&(currentHit.t_ < nearestHit.t_)){
      nearestHit = currentHit;
      //nearestHit.nearestShape_ = std::make_shared<Shape>(*i);
    }
  }
  return nearestHit;
}
