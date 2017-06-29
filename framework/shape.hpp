#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"

#include <glm/vec3.hpp>
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

  virtual bool intersect(Ray const& ray, float& t) = 0;

  //virtual: kann überschrieben werden
  virtual std::ostream& print(std::ostream& os) const;

  //non-virtual: nicht überschreiben
  std::string getName() const;
  Color getColor() const;
  Material getMaterial() const;



protected:
  //protected, damit die abgeleiteten drauf zugreifen können
  std::string name_;
  Color color_;
  Material material_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif //SHAPE_HPP
