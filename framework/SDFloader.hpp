#ifndef SDFLOADER_HPP
#define SDFLOADER_HPP

#include <iostream>
#include <fstream>

class SDFloader{
  /*bekommt einen file im SDF Format übergeben,
  *liest ihn ein und gibt eine Scene zurück
  */

  Scene loadScene(std::string const& fileIn);
};
#endif //SDFLOADER_HPP
