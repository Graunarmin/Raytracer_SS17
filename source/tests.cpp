#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

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
  //REQUIRE(box2.area() == 24);

}

TEST_CASE("Box Volume", "[5.2 Box Volume]"){
  Box box{};
  REQUIRE(box.volume() == 8);

  Box box2{glm::vec3{-1,-2,0}, glm::vec3{1,1,4}, "Coole Box", Color{1.0f, 1.0f, 1.0f}};
  //REQUIRE(box2.volume() == 8);
}

TEST_CASE("Sphere Area", "[5.2 Sphere Area]"){
  Sphere sphere{};
  REQUIRE(sphere.area() == Approx(12.56637f));

  Sphere sphere2{glm::vec3{-1,2,0}, 5.0f, "Coole Kugel", Color{1.0f, 1.0f, 1.0f}};
  //REQUIRE(sphere2.area() == Approx(12.56637f));
}

TEST_CASE("Sphere Volume", "[5.2 Sphere Volume]"){
  Sphere sphere{};
  REQUIRE(sphere.volume() == Approx(4.18879f));

  Sphere sphere2{glm::vec3{-1,2,0}, 5.0f, "Coole Kugel", Color{1.0f, 1.0f, 1.0f}};
  //REQUIRE(sphere2.volume() == Approx(4.18879f));
}

TEST_CASE("Print Sphere", "[5.5 print]"){
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
}


// TEST_CASE("Shape Destructor", "[5.7 Shape Destructor]"){
//   Shape s1{};
//   ~s1;
// }


int main(int argc, char *argv[])
{


  return Catch::Session().run(argc, argv);
}
