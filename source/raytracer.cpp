#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char* argv[])
{
  unsigned const width = 400;
  unsigned const height = 400;
  //std::string const filename = "./checkerboard.ppm";
  std::string const filename = "./Szene.ppm";
  std::string const filepath = "../../doc/szene.txt";
  //filename als instream anfragen
  Scene szene{};
  Scene superSzene = szene.SDFloader(filepath);
  superSzene.printScene();


  glm::vec3 beobachter{0.0f};
  //beobachter/camera später in scene!!
  glm::vec3 screenCenter{0.0f, 0.0f, -100.0f};

  Renderer app{width, height, filename, superSzene, beobachter, screenCenter};

  std::thread thr([&app]() { app.render(); });

  Window win{glm::ivec2{width,height}};


  while (!win.should_close()) {
    if (win.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      win.close();
    }
      win.show(app.colorbuffer());
  }

  thr.join();

  return 0;
}
