#include "SDFloader.hpp"

void SDFloader::print() const{
      std::cout<<"PrintMethode\n";
      for(const auto& i: materials_){
        std::cout<<"For Schleife\n";
        Material mp{i.name_, i.ka_, i.kd_, i.ks_, i.m_};
        std::cout<<mp;
      }
    }

// std::vector<Material> SDFloader::getVector() const{
//   return materials_;
// }

void SDFloader::addMaterial(Material const& mat){
  materials_.push_back(mat);
  // std::cout<<"Das Material\n";
  // std::cout << mat;
  // std::cout<<"Wurde echt gepusht!\n\n";
  // std::cout<< "Der Vektor sieht jetzt so aus: \n";
  // print(materials_);
  // std::cout<<"und ist hier zuende.\n\n";
}

void SDFloader::loadMaterial(std::string const& fileIn) const{
  SDFloader myLoader;

  //std::cout <<"Hi ich geh hier rein.\n";

    std::ifstream file;
    std::string line;
    file.open(fileIn);

    if(file.is_open()){
      //std::cout <<"File is open!\n";

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

            Material mat;

            ss>>mat.name_;
            //std::cout << "name: " << material.name_<<"\n";

            ss>> mat.ka_.r;
            ss>> mat.ka_.g;
            ss>> mat.ka_.b;
            ss>> mat.kd_.r;
            ss>> mat.kd_.g;
            ss>> mat.kd_.b;
            ss>> mat.ks_.r;
            ss>> mat.ks_.g;
            ss>> mat.ks_.b;
            ss>> mat.m_;

            // std::cout << mat;
            // std::cout<< "Wird gepusht.\n";
            myLoader.addMaterial(mat);

          }
        }
      }
      file.close();
      std::cout << "Hier der Vector mit den Materialien:\n";
    }

    myLoader.print();

  }
