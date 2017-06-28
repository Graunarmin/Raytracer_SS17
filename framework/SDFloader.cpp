#include "SDFloader.hpp"


  std::vector<Material> materials();

void SDFloader::loadMaterial(std::string const& fileIn) const{

    std::ifstream file;
    std::string line;
    file.open(fileIn);

    if(file.is_open()){
      while(std::getline(file,line)){
        std::stringstream ss;
        std::string keyword;



        ss<<line;
        ss>>keyword;
        std::cout << keyword;
      }

    }

    // Material beautifulMaterial;
    //
    // return beautifulMaterial;

  }
