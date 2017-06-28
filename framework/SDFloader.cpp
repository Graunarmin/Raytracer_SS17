
  std::vector<Material*> materials;

  Material SDFloader::loadMaterial(std::string const& fileIn) const{

    std::ifstream file;
    std::string line;
    sceneFile.open(fileIn);

    if(file.is_open()){
      while(){
        std::stringstream ss;
        std::string keyword;

        ss<<line;
        ss>>keyword;
      }

    }

    Material beautifulMaterial;

    return beautifulMaterial;

  }
