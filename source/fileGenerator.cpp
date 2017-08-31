#include "scene.hpp"
#include <renderer.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <sys/stat.h>


int main(int argc, char* argv[]) {

  std::string const filepath = "../../doc/animation.txt";
  Scene szene{};
  Scene superSzene = szene.SDFloader(filepath);


  const int frames = 120;
  std::vector<std::string> fileNames;
  std::vector<std::string> imageNames;

  //Vektoren mit den Namen für die Frameworks und Bilder generieren
  for(int i = frames; i >= 0; --i){
    fileNames.push_back("framework" + std::to_string(i) + ".txt");
    imageNames.push_back("image" + std::to_string(i) + ".ppm");
  }

  //txt Dateien schreiben - Namen für alle Files aus den Vektoren holen
  for(int i = 0; i < frames; ++i){
    std::string tmp = fileNames.back();
    std::ofstream afile("../../doc/TXT_Scenes/"+tmp, std::ios::out);
    fileNames.pop_back();
    if (afile.is_open()) {

      std::string im = imageNames.back();
      //Inhalte aus der Szene holen und in den File schreiben, ggf transformieren
          for(auto const& i: superSzene.materials_){
            i->toScene(afile);
          }

          for(auto const& i: superSzene.composite_->shapes_){
              i->transform();//transformiert das Objekt
              i->toScene(afile);//schreibt es in den file
          }
          //superSzene.camera_.around();
          superSzene.camera_.toScene(afile);

          for(auto const& i: superSzene.lights_){
            i->toScene(afile);
          }

          superSzene.ambientLight_.toScene(afile);

      afile
          <<"define shape composite root Boden Wand Kugel Box Kugel1 Kugel2 Box1"<<std::endl
          <<"transform Kugel translate 0.1 0 -0.1"<<std::endl
          <<"transform Box translate 0.2 0 -0.3 "<<std::endl 
          <<"transform Kugel1 translate -0.1 0 -0.1"<<std::endl
          <<"transform Kugel2 translate 0 0.1 0"<<std::endl 
          <<"transform Box1 translate 0 0 0.3"<<std::endl 
          <<"render cam ../../doc/PPM_Images/"<< im << " 400 400"<<std::endl;
      imageNames.pop_back();
      afile.close();
    }
  }
  return 0;
}
