#ifndef SCENE_HPP
#define SCENE_HPP

#include <cstdlib>
#include <vector>

struct Scene{

  //Smartpointer!!

  std::vector<Shape*> shapes;
  std::vector<Camera*> camera;
  std::vector<Light*> lights; //aufteilen in Grundbeleuchtung und Punktlichtquellen!
  std::vector<Ray*> rays;
  std::vector<Material*> materials;

  Scene loadScene(std::string const& fileIn){

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

    Scene beautifulScene;

    return beautifulScene;

  }


};
#endif //SCENE_HPP
