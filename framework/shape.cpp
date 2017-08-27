#include "shape.hpp"

Shape::Shape():
  name_{"Cooles Objekt"},
  material_{},
  world_transformation_{1.0f},
  world_transformation_inv_{1.0f}{}

Shape::Shape(std::string const& name, Color const& color):
  name_{name},
  color_{color}{}

Shape::Shape(std::string const& name, Material const& material):
  name_{name},
  material_{material},
  world_transformation_{1.0f},
  world_transformation_inv_{1.0f}
  {}

  Shape::~Shape()
  {
    //std::cout << "Deconstructor Base class Shape\n";
  }

  std::string Shape::getName() const{
    return name_;
  }

  Color Shape::getColor() const{
    return color_;
  }

  Material Shape::getMaterial() const{
    return material_;
  }

  std::ostream& Shape::print(std::ostream& os) const{
    // << für color gibt es schon in color.hpp
    // Name und color werden in os gepackt
    os << "Objektname: " << name_ << "\n"<<material_<<"\n";
    return os;
  }

  std::ostream& operator<<(std::ostream& os, Shape const& s){
    /*hier wird print aufgerufen, os per Referenz
    wird in print(os) ja verändert*/
    return s.print(os);
  }

  void Shape::translate(glm::vec3 const& v){
    glm::mat4 T;

    T[0] = {1,0,0,0};
    T[1] = {0,1,0,0};
    T[2] = {0,0,1,0};
    T[3] = {v.x,v.y,v.z,1};

    world_transformation_ *= T;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::rotate(float teta, glm::vec3 achse){   //Matrix reloaded 
  glm::mat4 R;

  if(achse.x == 1){
    R[0] = {1,0,0,0};
    R[1] = {0,cos(teta),sin(teta),0};
    R[2] = {0,-sin(teta),cos(teta),0};
    R[3] = {0,0,0,1};

    world_transformation_ *= R;
    world_transformation_inv_ = glm::inverse(world_transformation_);
  }
  else if(achse.y == 1){
    R[0] = {cos(teta),0,-sin(teta),0};
    R[1] = {0,1,0,0};
    R[2] = {sin(teta),0, cos(teta),0};
    R[3] = {0,0,0,1};

    world_transformation_ *= R;
    world_transformation_inv_ = glm::inverse(world_transformation_);
  }
  else if(achse.z == 1){
    R[0] = {cos(teta),sin(teta),0,0};
    R[1] = {-sin(teta), cos(teta),0,0};
    R[2] = {0,0,1,0};
    R[3] = {0,0,0,1};

    world_transformation_ *= R;
    world_transformation_inv_ = glm::inverse(world_transformation_);
  }
  else{
    std::cout << "-------ERROR-------- Not a valid axis -------ERROR-------- \n"; 
  }
}

void Shape::scale(glm::vec3 const& z){
  glm::mat4 S;

  S[0] = {z.x, 0, 0, 0};
  S[1] = {0, z.y, 0, 0};
  S[2] = {0, 0, z.z, 0};
  S[3] = {0, 0, 0, 1};

  world_transformation_ *= S;
  world_transformation_inv_ = glm::inverse(world_transformation_);
}
