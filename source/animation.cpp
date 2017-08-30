#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {

  const int frames = 3;
  std::vector<std::string> fileNames;
  std::vector<std::string> imageNames;

  //Vektoren mit den Namen für die Frameworks und Bilder generieren
  for(int i = frames; i > 0; --i){
    fileNames.push_back("framework" + std::to_string(i) + ".txt");
    imageNames.push_back("image" + std::to_string(i) + ".ppm");

  }

  for(int i = 0; i < frames; ++i){
    std::string tmp = fileNames.back();
    //std::ofstream fOut("../doc/"+tmp);

    std::ofstream afile("../../doc/TXT_Scenes/"+tmp, std::ios::out);
    fileNames.pop_back();
    if (afile.is_open()) {
      afile << "define material red 1 0 0 1 0 0 1 1 1 0 0 40"<<std::endl;
      //Hier Szenenbeschreibung einfügen
      afile.close();
    }

  }
  return 0;
}
