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

class Shape{

public:
  Shape();
  Shape(std::string const& name, Color const& color);
  Shape(std::string const& name, Material const& material);

  virtual ~Shape();

  //pure virtual: muss überschrieben werden
  virtual float area() const = 0;
  virtual float volume() const = 0;
  virtual OptionalHit intersect(Ray const& ray, float& t) = 0;
  virtual glm::vec3 computeNorm(OptionalHit const& hit) const = 0;
  //virtual Shape transform() = 0;
  virtual std::shared_ptr<Shape> transform() = 0;

  //virtual: kann überschrieben werden
  virtual std::ostream& print(std::ostream& os) const;

  //non-virtual: nicht überschreiben
  std::string getName() const;
  Color getColor() const;
  Material getMaterial() const;
  void translate(glm::vec3 const& v);
  void rotate(float teta, glm::vec3 achse);
  void scale(glm::vec3 const& s);


protected:
  //protected, damit die abgeleiteten drauf zugreifen können
  std::string name_;
  Color color_;
  Material material_;
  glm::mat4 world_transformation_;
  glm::mat4 world_transformation_inv_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif //SHAPE_HPP
