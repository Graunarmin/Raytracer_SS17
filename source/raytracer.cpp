#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <string>
#include <cmath>

int main(int argc, char* argv[])
{
  std::string const filepath = "../../doc/DieSzene.txt";

  //std::string const filepath = "../../doc/szene.txt";

  //std::string const filepath = "../../doc/szene1.txt";

  //std::string const filepath = "../../doc/animation.txt";

  //std::string const filepath = "../../doc/szene2.txt";

  Scene szene{};
  Scene superSzene = szene.SDFloader(filepath);
  superSzene.printScene();

  //glm::vec3 screenCenter{0.0f, 0.0f, -100.0f};

  Renderer app{superSzene/*, screenCenter*/};

  std::thread thr([&app]() { app.render(); });

  Window win{glm::ivec2{superSzene.width_,superSzene.height_}};


  while (!win.should_close()) {
    if (win.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      win.close();
    }
      win.show(app.colorbuffer());
  }

  thr.join();

  return 0;
}
