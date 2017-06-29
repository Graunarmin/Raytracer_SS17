#include "SDFloader.hpp"


  std::vector<Material> materials(2);

  void print(const std::vector<Material> &mat){
    for(const auto& i: mat){
      std::cout << i << ' ';
      std::cout << std::endl;
    }
  }

void SDFloader::loadMaterial(std::string const& fileIn) const{
  std::cout <<"Hi ich geh hier rein.\n";

    std::ifstream file;
    std::string line;
    file.open(fileIn);

    if(file.is_open()){
      std::cout <<"File is open!\n";
      while(std::getline(file,line)){
        std::stringstream ss;
        std::string keyword;

        ss<<line;
        ss>>keyword;
        //std::cout << "keyword: " << keyword <<"\n";

        if(keyword == "define"){
          ss<<line;
          ss>>keyword;
          //std::cout << "Nächstest keyword: " << keyword <<"\n";

          if(keyword == "material"){
            //material erstellen:
            // std::string name_;
            // Color ka_;
            // Color kd_;
            // Color ks_;
            // float m_;


            Material material;

            ss>>material.name_;
            //std::cout << "name: " << material.name_<<"\n";

            ss>> material.ka_.r;
            ss>> material.ka_.g;
            ss>> material.ka_.b;
            ss>> material.kd_.r;
            ss>> material.kd_.g;
            ss>> material.kd_.b;
            ss>> material.ks_.r;
            ss>> material.ks_.g;
            ss>> material.ks_.b;
            ss>> material.m_;

            std::cout << material;
            std::cout<< "Wird gepusht.";
            materials.push_back(material);

          }
          std::cout<< "Vector: ";
          print(materials);


        }
      }

    }

    // Material beautifulMaterial;
    //
    // return beautifulMaterial;

  }
