#include "scene.hpp"

void Scene::loadScene(std::string const& fileIn) const{
  Scene myScene;

  std::ifstream file;
  std::string line;
  file.open(fileIn);

  if(file.is_open()){

    while(std::getline(file,line)){
      std::stringstream ss;
      std::string keyword;

      ss<<line;
      ss>>keyword;

      if(keyword == "define"){
        ss<<line;
        ss>>keyword;

        if(keyword == "material"){

          Material mat;

          ss>>mat.name_;

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

          myScene.addMaterial(mat);
        }
      }
    }
    file.close();
  }
  myScene.print();

}

void Scene::addMaterial(Material const& mat){
  auto p = std::make_shared<Material>(mat);
  materials_.push_back(p);
  std::cout<< p->name_<<" wird gepusht.\n\n";
}

void Scene::print() const{
      std::cout<<"PrintMethode\n";
      for(const auto& i: materials_){
        std::cout<<"For Schleife\n";
        Material mp{i->name_, i->ka_, i->kd_, i->ks_, i->m_};
        std::cout<<mp;
      }
    }
