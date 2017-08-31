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
  for(int i = frames; i > 0; --i){
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

      afile
          <<"define material grey  0.8 0.8 0.9 0.8 0.8 0.9 0.8 0.8 0.9 2 0 1"<<std::endl
          <<"define material matteGrey 0.8 0.8 0.9 0.8 0.8 0.9 0 0 0 2 0 1"<<std::endl
          <<"define material reflectiveDarkGrey 0.8 0.8 0.9 0.3 0.3 0.3 1 1 1 200 0 1"<<std::endl
          <<"define material pinkGlass 1 0 0.5 1 0 0.5 0.5 0.5 0.5 200 2.4 20"<<std::endl
          <<"define material lightblue 0.45 0.615 1 0.45 0.615 1 0.45 0.615 1 810 1.5 3"<<std::endl;

          for(auto const& i: superSzene.composite_->shapes_){
              i->transform();//transformiert das Objekt
              i->toScene(afile);//schreibt es in den file
          }
          superSzene.camera_.around();
          superSzene.camera_.toScene(afile);

      afile
          <<"define light ambient 0 0 0 0.5 0.5 0.5 0 0 0"<<std::endl
          <<"define light light3 -15 10 -20 0.6 0.6 0.6 1.0 1.0 1.0"<<std::endl
          <<"define shape composite root Boden Wand Kugel"<<std::endl
          <<"transform Kugel translate 1 0 -1"<<std::endl
          <<"render cam ../../doc/PPM_Images/"<< im << " 400 400"<<std::endl;
      imageNames.pop_back();
      afile.close();
    }
  }


  // for(int i = 0; i < frames; ++i){
  //   std::string path = "../../doc/TXT_Scenes/framework"+std::to_string(i)+".txt";
  //   Scene scene{};
  //   Scene tolleSzene = scene.SDFloader(path);
  //   //superSzene.printScene();
  //
  //   Renderer app{tolleSzene};
  //
  //   std::thread thr([&app]() { app.render(); });
  //
  //   thr.join();
  //
  // }
  return 0;
}
