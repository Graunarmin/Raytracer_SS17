#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>
#include <iostream>
#include "color.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <fstream>

struct Light{

  Light():
    name_{"Default Light"},
    position_{0.0f},
    ia_{0.0f},
    ip_{0.0f}{}

  Light(std::string name, glm::vec3 pos, Color ia, Color ip):
    name_{name},
    position_{pos},
    ia_{ia},
    ip_{ip}{}

  void toScene(std::ofstream& file){
    file<<"define light "<<name_<<" "<<position_.x<<" "<<position_.y<<" "<<position_.z<<" "
        <<ia_.r<<" "<<ia_.g<<" "<<ia_.b<<" "<<ip_.r<<" "<<ip_.g<<" "<<ip_.b<<std::endl;
  }

  friend std::ostream& operator<<(std::ostream& os, Light const& light){
    os << "Name der Lichtquelle: " << light.name_<< std::endl <<
        "Position: (" << light.position_.x <<", "<< light.position_.y<<", "<<
         light.position_.z<<")" <<std::endl <<
        "Ambiente Beleuchtung: " <<light.ia_<< std::endl <<
        "Diffuse Beleuchtung: " << light.ip_ << std::endl;
    return os;
  }

  std::string name_;
  glm::vec3 position_;
  Color ia_;
  Color ip_;

};
#endif //LIGHT_HPP
