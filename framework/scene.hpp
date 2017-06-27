#ifndef SCENE_HPP
#define SCENE_HPP

struct scene{

  std::vector<Shape*> shapes;
  std::vector<Camera*> camera;
  std::vector<Light*> lights; //aufteilen in Grundbeleuchtung und Punktlichtquellen!
  std::vector<Ray*> rays;

};
#endif //SCENE_HPP
