#ifndef MATERIAL_HPP
#define MATERIAL_HPP

struct Material{

//Konstruktoren
  Material():
    name_{"Cooles Material"},
    ka_{Color{}},
    kd_{Color{}},
    ks_{Color{}},
    m_{0.0f}{}

  Material(std::string name, color a, color d, color s, float m):
    name_{name},
    ka_{a},
    kd_{d},
    ks_{s},
    m_{m}{}

  std::ostream& operator<<(std::ostream& os, Material const& mat){
    os << "(" << mat.name_ << "," << mat.ka_ << "," << mat.kd_ <<
            "," << mat.ks_ << "," << mat.m_ << ")\n";
    return os;
  }

//Member
  std::string name_;
  color ka_;
  color kd_;
  color ks_;
  float m_;
};
#endif //MATERIAL_HPP
