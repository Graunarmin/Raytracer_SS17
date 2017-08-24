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
        //ss<<line;
        ss>>keyword;

        if(keyword == "material"){

          Material mat;

          ss>> mat.name_;
          ss>> mat.ka_.r;
          ss>> mat.ka_.g;
          ss>> mat.ka_.b;
          ss>> mat.kd_.r;
          ss>> mat.kd_.g;
          ss>> mat.kd_.b;
          ss>> mat.ks_.r;
          ss>> mat.ks_.g;
          ss>> mat.ks_.b;
          //std::cout<<"Hauptfunktion: vorletzter Materialwert: "<<mat.ks_.b<<"\n";
          ss>> mat.m_;
          //std::cout<<"Hauptfunktion: letzter Materialwert: "<<mat.m_<<"\n";

          myScene.addMaterial(mat);
        }//if material zu

        if(keyword == "light"){
          Light light;

          ss>>light.name_;
          ss>>light.position_.x;
          ss>>light.position_.y;
          ss>>light.position_.z;
          ss>>light.ia_.r;
          ss>>light.ia_.g;
          ss>>light.ia_.b;
          ss>>light.ip_.r;
          ss>>light.ip_.g;
          ss>>light.ip_.b;

          if(light.name_ == "ambient"){
            std::cout<<"Das ambiente Licht: "<< light<<"\n";
            myScene.ambientLight_ = light;
          }//if zu
          else{
            myScene.addLight(light);
          }//else zu
        }//if light zu

        if(keyword == "shape"){
          //ss<<line;
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
              //std::cout<<"Geht in die For-Schleife.\n";
              if(i->name_ == keyword){
                Box box{bMin, bMax, bName, Material{i->name_, i->ka_, i->kd_, i->ks_, i->m_}};
                myScene.addBox(box);
                //myScene.addShape(box);
                break;
              }//if zu
            }//for zu

          }//if-box zu

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
                //myScene.addShape(sphere);
                break;
              }//if zu
            }//for zu

          }//if sphere zu

          if(keyword == "composite"){
            std::string cName;
            std::string shapeName;

            ss>>cName;
            //???


            while(!ss.eof()){


            }//while zu

          }//if composite zu
      }//if shape zu

    }//if define zu
  }//while zu
    file.close();
  }//if is-open zu

  //myScene.printScene();

  return myScene;
}//Fkt zu

void Scene::addMaterial(Material const& mat){
  auto p = std::make_shared<Material>(mat);
  materials_.push_back(p);
  //std::cout<<"AddMaterial Funktion: "<< p->name_<<" wird gepusht.\n\n";
}

void Scene::addBox(Box const& b){
  auto p = std::make_shared<Box>(b);
  boxes_.push_back(p);
  shapes_.push_back(p);
  //std::cout<<"AddBox Funktion: "<<p->getName()<<" wird gepusht.\n\n";
}

void Scene::addSphere(Sphere const& s){
  auto p = std::make_shared<Sphere>(s);
  spheres_.push_back(p);
  shapes_.push_back(p);
  //std::cout<<"AddSphere Funktion: "<<p->getName()<<" wird gepusht.\n\n";
}

void Scene::addLight(Light const& l){
  auto p = std::make_shared<Light>(l);
  lights_.push_back(p);
  //std::cout<<"AddLight Funktion: "<<p->name_<<" wird gepusht.\n\n";
}

void Scene::printScene() const{
      std::cout<<"printScene Funktion:\n"<<"Materiealien der Szene:\n";
      for(const auto& i: materials_){
        Material mp = *i;
        std::cout<<mp;
      }

      std::cout<<"\nObjekte der Szene:\n";

      // for(const auto& i: boxes_){
      //   std::cout<< *i;
      // }
      //
      // for(const auto& i: spheres_){
      //   std::cout<< *i;
      // }
      //
      // std::cout<<"Und im Shapes Container stehen: \n";
      for(const auto& i: shapes_){
        std::cout<< *i;
      }

      std::cout<<"\nLichtquellen der Szene:\n";
      for(const auto& i: lights_){
        Light l = *i;
        std::cout<<l;
      }

    }
