#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <iostream>
#include <fstream>
#include "color.hpp"

struct Material{

//Konstruktoren
  Material():
    name_{"Cooles Material"},
    ka_{Color{}},
    kd_{Color{}},
    ks_{Color{}},
    m_{0.0f}{}

  //Für die Tests muss er bleiben!
  Material(std::string const& name, Color const& a, Color const& d, Color const& s, float m):
    name_{name},
    ka_{a},
    kd_{d},
    ks_{s},
    m_{m}{}

  Material(std::string const& name, Color const& a, Color const& d, Color const& s, float m, float opacity, float ri):
    name_{name},
    ka_{a},
    kd_{d},
    ks_{s},
    m_{m},
    opacity_{opacity},
    ri_{ri} {}

void toScene(std::ofstream& file){
      file<<"define material "<<name_<<" "<<ka_.r<<" "<<ka_.g<<" "<<ka_.b<<" "
          <<kd_.r<<" "<<kd_.g<<" "<<kd_.b<<" "<<ks_.r<<" "<<ks_.g<<" "<<ks_.b<<" "
          <<m_<<" "<<ri_<<" "<<opacity_<<std::endl;
    }


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
  float ri_;
  float opacity_;
};
#endif //MATERIAL_HPP
