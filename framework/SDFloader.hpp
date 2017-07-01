#ifndef SDFLOADER_HPP
#define SDFLOADER_HPP

#include "material.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class SDFloader{
  /*bekommt einen file im SDF Format übergeben,
  *liest ihn ein und gibt eine Scene zurück
  */
public:
  //Methoden
  void loadMaterial(std::string const& fileIn) const;
  void addMaterial(Material const& m);
  void print() const;
  //std::vector<Material> getVector() const;

  //Member
private:
  std::vector<Material> materials_;

};
#endif //SDFLOADER_HPP
