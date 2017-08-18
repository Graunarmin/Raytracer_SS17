#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "material.hpp"
#include "scene.hpp"

//Konstruktoren Tests, implizieren getter
TEST_CASE("Box Default Constructor", "[5.2 Box Constructor]"){
  Box box{};
  REQUIRE(box.getMin().x == -1);
  REQUIRE(box.getMin().y == -1);
  REQUIRE(box.getMin().z == -1);
  REQUIRE(box.getMax().x == 1);
  REQUIRE(box.getMax().y == 1);
  REQUIRE(box.getMax().z == 1);
}

TEST_CASE("Box Constructor", "[5.2 Box Constructor]"){
  Box box{glm::vec3{-1,-2,0}, glm::vec3{1,1,4}, "Coole Box", Color{1.0f, 1.0f, 1.0f}};
  REQUIRE(box.getMin().x == -1);
  REQUIRE(box.getMin().y == -2);
  REQUIRE(box.getMin().z == -0);
  REQUIRE(box.getMax().x == 1);
  REQUIRE(box.getMax().y == 1);
  REQUIRE(box.getMax().z == 4);
  REQUIRE(box.getName() == "Coole Box");
}

TEST_CASE("Box Constructor 2", "[5.2 Box Constructor]"){
  Box box{glm::vec3{5, 2, -6}, glm::vec3{-2, -4, 3}, "Coole Box", Color{1.0f, 1.0f, 1.0f}};
  REQUIRE(box.getMin().x == -2);
  REQUIRE(box.getMin().y == -4);
  REQUIRE(box.getMin().z == -6);
  REQUIRE(box.getMax().x == 5);
  REQUIRE(box.getMax().y == 2);
  REQUIRE(box.getMax().z == 3);
  REQUIRE(box.getName() == "Coole Box");
}

TEST_CASE("Sphere Default Constructor", "[5.2 Sphere Constructor]"){
  Sphere sphere{};
  REQUIRE(sphere.getCenter().x == 0.0f);
  REQUIRE(sphere.getCenter().y == 0.0f);
  REQUIRE(sphere.getCenter().z == 0.0f);
  REQUIRE(sphere.getRadius() == 1.0f);
  REQUIRE(sphere.getName() == "Cooles Objekt");
}

TEST_CASE("Sphere Constructor", "[5.2 Sphere Constructor]"){
  Sphere sphere{glm::vec3{-1,2,0}, 5.0f, "Coole Kugel", Color{1.0f, 1.0f, 1.0f}};
  REQUIRE(sphere.getCenter().x == -1.0f);
  REQUIRE(sphere.getCenter().y == 2.0f);
  REQUIRE(sphere.getCenter().z == 0.0f);
  REQUIRE(sphere.getRadius() == 5.0f);
  REQUIRE(sphere.getName() == "Coole Kugel");
  REQUIRE(sphere.getColor().r == 1.0f);
  REQUIRE(sphere.getColor().g == 1.0f);
  REQUIRE(sphere.getColor().b == 1.0f);

}

TEST_CASE("Box Area", "[5.2 Box Area]"){
  Box box{};
  REQUIRE(box.area() == 24);

  Box box2{glm::vec3{-1,-2,0}, glm::vec3{1,1,4}, "Coole Box", Color{1.0f, 1.0f, 1.0f}};
  REQUIRE(box2.area() == 52.0f);

}

TEST_CASE("Box Volume", "[5.2 Box Volume]"){
  Box box{};
  REQUIRE(box.volume() == 8);

  Box box2{glm::vec3{-1,-2,0}, glm::vec3{1,1,4}, "Coole Box", Color{1.0f, 1.0f, 1.0f}};
  REQUIRE(box2.volume() == 24.0f);
}

TEST_CASE("Sphere Area", "[5.2 Sphere Area]"){
  Sphere sphere{};
  REQUIRE(sphere.area() == Approx(12.56637f));

  Sphere sphere2{glm::vec3{-1,2,0}, 5.0f, "Coole Kugel", Color{1.0f, 1.0f, 1.0f}};
  REQUIRE(sphere2.area() == Approx(314.15926f));
}

TEST_CASE("Sphere Volume", "[5.2 Sphere Volume]"){
  Sphere sphere{};
  REQUIRE(sphere.volume() == Approx(4.18879f));

  Sphere sphere2{glm::vec3{-1,2,0}, 5.0f, "Coole Kugel", Color{1.0f, 1.0f, 1.0f}};
  REQUIRE(sphere2.volume() == Approx(523.59877f));
}

TEST_CASE("Print Sphere", "[5.5 print]"){
  std::cout<<"------5.5 Noch mit Color statt Material-------\n";
  Sphere sphere2{glm::vec3{-1,2,0}, 5.0f, "Coole Kugel", Color{1.0f, 1.0f, 1.0f}};
  std::cout << sphere2;
}

TEST_CASE("Print Box", "[5.5 print]"){
  Box box2{glm::vec3{-1,-2,0}, glm::vec3{1,1,4}, "Coole Box", Color{1.0f, 1.0f, 1.0f}};
  std::cout << box2;
}

TEST_CASE("intersectRaySphere", "[5.6 intersect]"){
  // Ray
  glm::vec3 ray_origin{0.0 ,0.0 ,0.0};
  // ray direction has to be normalized!
  // you can use:
  // v = glm :: normalize (some_vector)
  glm::vec3 ray_direction{0.0 ,0.0 ,1.0};
  // Sphere
  glm::vec3 sphere_center{0.0 ,0.0 ,5.0};
  float sphere_radius{1.0};
  float distance{0.0};
  auto result = glm::intersectRaySphere(
      ray_origin, ray_direction,
      sphere_center,
      sphere_radius * sphere_radius, // squared radius !!!
      distance);
  REQUIRE(distance == Approx(4.0f));
}

TEST_CASE("Sphere method intersect", "[5.6 intersect]"){

  glm::vec3 ray_origin{0.0 ,0.0 ,-2.0};
  glm::vec3 ray_direction{0.0 ,0.0 ,2.5};

  glm::vec3 sphere_center{0.0 ,0.0 ,4.0};
  float sphere_radius{1.0};
  float distance{0.0};

  Ray ray{ray_origin, ray_direction};
  Sphere sphere{sphere_center, sphere_radius, "Beautiful Sphere", Color{1.0f, 1.0f, 1.0f}};

  sphere.intersect(ray, distance);
  REQUIRE(distance == Approx(5.0f));

  glm::vec3 ray2_origin{0.0 ,8.0 ,-2.0};
  glm::vec3 ray2_direction{0.0 ,0.0 ,-7.0};

  glm::vec3 sphere2_center{-1.0 ,3.0 ,4.0};
  float sphere2_radius{2.0};
  float distance2{8.0};

  Ray ray2{ray2_origin, ray2_direction};
  Sphere sphere2{sphere2_center, sphere2_radius, "Beautiful Sphere", Color{1.0f, 1.0f, 1.0f}};

  sphere.intersect(ray2, distance2);
  REQUIRE(distance2 == Approx(8.0f));
}


// TEST_CASE("Destructor", "[5.8 Destructor]"){
//   std::cout << "---------------------------------------\n";
//   std::cout<< "Ab hier ist wichtig, hier geht 5.8 los:" << std::endl;
//   std::cout<<"Box Objekt anlegen:" << std::endl;
//   Shape* s = new Box;
//   std::cout << "Box wieder loeschen:" << std::endl;
//   delete s;
//
//   std::cout << "---------------------------------------\n";
//   std::cout<< "Und jetzt mit Sphere:" << std::endl;
//   std::cout<<"Sphere Objekt anlegen:" << std::endl;
//   Shape* s2 = new Sphere;
//   std::cout << "Sphere wieder loeschen:" << std::endl;
//   delete s2;
//   std::cout << "---------------------------------------\n";
// }
//
// TEST_CASE("Destructor 2", "[5.8 Destructor]"){
//   std::cout << "---------------------------------------\n";
//   std::cout<< "5.8 Test 2:" << std::endl;
//   Color red{255, 0, 0};
//   glm::vec3 position{0};
//   std::cout<<"Sphere Objekt anlegen:" << std::endl;
//   Sphere* s1 = new Sphere{position,1.2,"sphere0",red};
//   std::cout<<"Noch eins anlegen:" << std::endl;
//   Shape* s2 = new Sphere{position,1.2,"sphere1",red};
//   s1->print(std::cout);
//   s2->print(std::cout);
//   std::cout << "Sphere wieder loeschen:" << std::endl;
//   delete s1;
//   std::cout << "Und das andere auch wieder loeschen:" << std::endl;
//   delete s2;
//   std::cout << "---------------------------------------\n";
// }

TEST_CASE("Ray intersects Box", "[6.3 intersect]"){

  //Strahl z-Richtung
  glm::vec3 ray_origin{0.0 ,0.0 ,0.0};
  glm::vec3 ray_direction{0.0 ,0.0 ,1.0};
  Ray ray{ray_origin, ray_direction};
  float distance{0.0};

  Box box{glm::vec3{-2,-2,1}, glm::vec3{2,6,5}, "Zu schneidende Box",
          Material{}};
  REQUIRE(box.intersect(ray, distance));
  REQUIRE(distance == 1.0f);

  //Strahl y-Richtung
  glm::vec3 ray_origin2{0.0 ,0.0 ,0.0};
  glm::vec3 ray_direction2{0.0 ,1.0 ,0.0};
  Ray ray2{ray_origin2, ray_direction2};
  float distance2{0.0};

  Box box2{glm::vec3{-2,-2,-2}, glm::vec3{2,6,5}, "Zu schneidende Box",
          Material{}};

  REQUIRE(box2.intersect(ray2, distance2));
  REQUIRE(distance2 == 2);

  //Strahl in x-Richtung
  glm::vec3 ray_origin3{0.0 ,0.0 ,0.0};
  glm::vec3 ray_direction3{1.0 ,0.0 ,0.0};
  Ray ray3{ray_origin3, ray_direction3};
  float distance3{0.0};

  Box box3{glm::vec3{-2,-2,-2}, glm::vec3{2,6,5}, "Zu schneidende Box",
          Material{}};

  auto b = box3.intersect(ray3, distance3);

  REQUIRE(b);
  REQUIRE(distance3 == 2.0f);
}

TEST_CASE("Ray doesn't intersect Box", "[6.3 intersect]"){
  glm::vec3 ray_origin{0.0 ,0.0 ,0.0};
  glm::vec3 ray_direction{0.0 ,0.0 ,1.0};
  Ray ray{ray_origin, ray_direction};
  float distance{0.0};

  Box box{glm::vec3{-2,2,1}, glm::vec3{2,6,5}, "Nicht zu schneidende Box",
          Material{}};
  REQUIRE(!box.intersect(ray, distance));
}

TEST_CASE("Material Default Constructor", "[6.4 Material]"){
  Material m1{};
  REQUIRE(m1.name_ == "Cooles Material");
  REQUIRE(m1.ka_.r == 0.0f);
  REQUIRE(m1.m_ == 0.0f);
}

TEST_CASE("Material Constructor", "[6.4 Material]"){
  Material m1{"Awesome Material", Color{1.0f, 0.0f, 1.0f}, Color{}, Color{}, 1.3f};
  REQUIRE(m1.name_ == "Awesome Material");
  REQUIRE(m1.ka_.r == 1.0f);
  REQUIRE(m1.kd_.g == 0.0f);
  REQUIRE(m1.m_ == 1.3f);
}

TEST_CASE("Print Material", "[6.4 Material]"){
    std::cout<<"------------------6.4-----------------\n";
    Material m1{"Awesome Material", Color{1.0f, 0.0f, 1.0f}, Color{}, Color{}, 1.3f};
    std::cout << m1;
}


// TEST_CASE("SDF loader Material", "[6.5 SDF loader]"){
//   std::cout<<"--------------------6.5-----------------\n";
//
//   SDFloader loader{};
//   loader.loadMaterial("../programmiersprachen-raytracer/doc/material.txt");
//   //../../doc/..
// }

TEST_CASE("Struct Scene", "[6.6 Scene]"){
  std::cout<<"--------------------6.6-----------------\n";
  Scene cooleSzene{};

  Scene nSzene = cooleSzene.SDFloader("../../doc/material.txt");

  nSzene.printScene();
}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
