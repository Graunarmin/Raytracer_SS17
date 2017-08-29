#ifndef SCENE_HPP
#define SCENE_HPP

#include "material.hpp"
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "composite.hpp"
#include"camera.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

struct Scene{

  Scene SDFloader(std::string const& fileIn) const;
  void addMaterial(Material const& m);
  void addBox(Box const& b);
  void addSphere(Sphere const& s);
  void addLight(Light const& l);
  void printScene() const;



  //Smartpointer!!
  std::shared_ptr<Composite> composite_;
  //std::vector<std::shared_ptr<Shape>> shapes_;
  std::vector<std::shared_ptr<Light>> lights_;
  std::vector<std::shared_ptr<Material>> materials_;

  Light ambientLight_;
  Camera camera_;
  std::string filename_;
  unsigned width_;
  unsigned height_;
};
#endif //SCENE_HPP
