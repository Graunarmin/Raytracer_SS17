#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {

  const int frames = 10;
  std::vector<std::string> fileNames;
  std::vector<std::string> imageNames;

  //Vektoren mit den Namen für die Frameworks und Bilder generieren
  for(int i = frames; i > 0; --i){
    fileNames.push_back("framework" + std::to_string(i) + ".txt");
    imageNames.push_back("image" + std::to_string(i) + ".ppm");

  }

  //txt Dateien schreiben - Namen für alle Files aus den 
  for(int i = 0; i < frames; ++i){
    std::string tmp = fileNames.back();
    std::ofstream afile("../../doc/TXT_Scenes/"+tmp, std::ios::out);
    fileNames.pop_back();
    if (afile.is_open()) {
      std::string im = imageNames.back();

      afile
          <<"define material lightblue 0.45 0.615 1 0.45 0.615 1 0.45 0.615 1 810 1.5 3" <<std::endl
          <<"define material matteGrey 0.8 0.8 0.9 0.8 0.8 0.9 0 0 0 2 0 1" <<std::endl
          <<"define shape box Boden -21.5 -6 -6 21.6 -5.9 -37 matteGrey"<<std::endl
          <<"define shape sphere Kugel -4 -3.7 -18 2.2 lightblue"<<std::endl
          <<"define light ambient 0 0 0 0.5 0.5 0.5 0 0 0"<<std::endl
          <<"define light light3 -15 10 -20 0.6 0.6 0.6 1.0 1.0 1.0"<<std::endl
          <<"define camera cam 45"<<std::endl
          <<"define shape composite root Boden Kugel"<<std::endl
          <<"render cam ../../doc/PPM_Images/"<< im << " 400 400"<<std::endl
          <<"transform Kugel translate 3 0 2"<<std::endl;
      imageNames.pop_back();
      afile.close();
    }

  }
  return 0;
}
