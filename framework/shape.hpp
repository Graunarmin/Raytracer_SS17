#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "optionalHit.hpp"

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include <iostream>
#include <string>
//#include <sys/stat.h>
#include <fstream>

class Shape{

public:

  //Konstruktoren
  Shape();
  Shape(std::string const& name, Color const& color);
  Shape(std::string const& name, Material const& material);

  virtual ~Shape();

  //pure virtual: muss überschrieben werden, hier nur deklariert
  virtual float area() const = 0;
  virtual float volume() const = 0;

  virtual OptionalHit intersect(Ray const& ray, float& t) const = 0;
  virtual glm::vec3 computeNorm(OptionalHit const& hit) const = 0;
  virtual void transform() = 0;
  virtual void toScene(std::ofstream& file) const = 0;

  //virtual: kann überschrieben werden, hier auch definiert
  virtual std::ostream& print(std::ostream& os) const;

  //non-virtual: nicht überschreiben
  std::string const& getName() const;
  Color const& getColor() const;
  Material const& getMaterial() const;
  void translate(glm::vec3 const& v);
  void rotate(float teta, glm::vec3 const& achse);
  void scale(glm::vec3 const& s);
  glm::mat4 const& getWorldTrans() const;
  glm::mat4 const& getInvWorldTrans() const;



protected:

  //protected, damit die abgeleiteten drauf zugreifen können
  std::string name_;
  Color color_;
  Material material_;
  glm::mat4 world_transformation_;
  glm::mat4 world_transformation_inv_;
};

//Wird nicht auf Objekt aufgerufen (Bei std::cout << verwendet)
std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif //SHAPE_HPP
