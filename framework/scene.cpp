#include "scene.hpp"

Scene Scene::SDFloader(std::string const& fileIn) const{
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

        if(keyword == "shape"){
          ss>>keyword;

          if(keyword == "box"){
            std::string bName;
            glm::vec3 bMin;
            glm::vec3 bMax;

            ss>>bName;
            ss>>bMin.x;
            ss>>bMin.y;
            ss>>bMin.z;
            ss>>bMax.x;
            ss>>bMax.y;
            ss>>bMax.z;
            ss>>keyword;

            for(const auto& i: myScene.materials_){
              if(i->name_ == keyword){
                Box box{bMin, bMax, bName, Material{i->name_, i->ka_, i->kd_, i->ks_, i->m_}};
                myScene.addBox(box);
                break;
              }
            }
          }

          if(keyword == "sphere"){
            std::string sName;
            glm::vec3 sCenter;
            float sRad;


            ss>>sName;
            ss>>sCenter.x;
            ss>>sCenter.y;
            ss>>sCenter.z;
            ss>>sRad;
            ss>>keyword;

            for(const auto& i: myScene.materials_){
              if(i->name_ == keyword){
                Sphere sphere{sCenter, sRad, sName, Material{i->name_, i->ka_, i->kd_, i->ks_, i->m_}};
                myScene.addSphere(sphere);
                break;
              }
            }

          }
      }
    }
  }
    file.close();
  }

  //myScene.printScene();

  return myScene;

}

void Scene::addMaterial(Material const& mat){
  auto p = std::make_shared<Material>(mat);
  materials_.push_back(p);
  std::cout<< p->name_<<" wird gepusht.\n\n";
}

void Scene::addBox(Box const& b){
  auto p = std::make_shared<Box>(b);
  boxes_.push_back(p);
  std::cout<<"AddBox Funktion: "<<p->getName()<<" wird gepusht.\n\n";
}

void Scene::addSphere(Sphere const& s){
  auto p = std::make_shared<Sphere>(s);
  spheres_.push_back(p);
  std::cout<<"AddSphere Funktion: "<<p->getName()<<" wird gepusht.\n\n";
}

// void Scene::addLight(Light const& l){
//   auto p = std::make_shared<Light>(l);
//   lights_.push_back(p);
//   std::cout<<"AddLight Funktion: "<<p->name_<<" wird gepusht.\n\n";
// }


void Scene::printScene() const{
    std::cout<<"printScene Funktion:\n"<<"Materiealien der Szene:\n";
    for(const auto& i: materials_){
      Material mp = *i;
      std::cout<<mp;
    }

        std::cout<<"\nObjekte der Szene:\n";
        for(const auto& i: boxes_){
          Box b = *i;
          std::cout<<b;
        }

        for(const auto& i: spheres_){
          Sphere s = *i;
          std::cout<<s;
        }
      }
