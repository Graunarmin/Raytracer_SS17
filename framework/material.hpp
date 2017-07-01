#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <iostream>
#include "color.hpp"

struct Material{

//Konstruktoren
  Material():
    name_{"Cooles Material"},
    ka_{Color{}},
    kd_{Color{}},
    ks_{Color{}},
    m_{0.0f}{}

  Material(std::string name, Color a, Color d, Color s, float m):
    name_{name},
    ka_{a},
    kd_{d},
    ks_{s},
    m_{m}{}

  //friend, da es ja aus der Shape aufgerufen wird!
  friend std::ostream& operator<<(std::ostream& os, Material const& mat){
    os << "Materialname: " << mat.name_ << std::endl <<
          "ka: " << mat.ka_ << std::endl<<
          "kd: " << mat.kd_ <<std::endl<<
          "ks: " << mat.ks_ << std::endl<<
          "m: " << mat.m_ << std::endl;
    return os;
  }

//Member
  std::string name_;
  Color ka_;
  Color kd_;
  Color ks_;
  float m_;
};
#endif //MATERIAL_HPP
