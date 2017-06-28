#ifndef SDFLOADER_HPP
#define SDFLOADER_HPP

#include "material.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class SDFloader{
  /*bekommt einen file im SDF Format übergeben,
  *liest ihn ein und gibt eine Scene zurück
  */
public:
  void loadMaterial(std::string const& fileIn) const;
};
#endif //SDFLOADER_HPP
