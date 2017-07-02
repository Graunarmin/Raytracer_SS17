#ifndef SCENE_HPP
#define SCENE_HPP

#include "material.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct Scene{

  Scene loadScene(std::string const& fileIn) const;
  void addMaterial(Material const& m);
  void printScene() const;


  //Smartpointer!!
  // std::vector<std::shared_ptr<Shape>> shapes_;
  // std::vector<std::shared_ptr<Box>> boxes_;
  // std::vector<std::shared_ptr<Sphere>> spheres_;
  // std::vector<std::shared_ptr<Camera>> camera_;
  // std::vector<std::shared_ptr<Light>> lights_; //aufteilen in Grundbeleuchtung und Punktlichtquellen!
  // std::vector<std::shared_ptr<Ray>> rays_;
  std::vector<std::shared_ptr<Material>> materials_;
};
#endif //SCENE_HPP
