#include <renderer.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <string>
#include <cmath>


int main(int argc, char* argv[]) {

  for(int i = 0; i < 10; ++i){
    std::string filepath = "../../doc/TXT_Scenes/framework"+std::to_string(i)+".txt";
    Scene szene{};
    Scene superSzene = szene.SDFloader(filepath);
    //superSzene.printScene();

    Renderer app{superSzene};

    std::thread thr([&app]() { app.render(); });

    thr.join();

  }
  return 0;
}
