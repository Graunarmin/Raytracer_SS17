// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "scene.hpp"
#include "box.hpp"
#include "camera.hpp"
#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>
#include <cmath>
#include <iostream>
#include <limits>
#include <typeinfo>
#include <cstdlib>
#include <random>

class Renderer
{
public:
  Renderer(Scene const& scene/*, glm::vec3 const& ce*/);

  void render();
  OptionalHit hitBox(Ray const& ray);
  OptionalHit hitSphere(Ray const& ray);
  OptionalHit hitObject(Ray const& ray);
  Color raytracer(Ray const& ray, int depth);
  Color compColor(OptionalHit const& nH, glm::vec3 const& n,
  glm::vec3 const& v, int depth, Ray const& ray);
  void write(Pixel const& p);
  void ambientLight(Color const& summeDif, Material const& m, Color& i);
  void pointLight(Color& summeDif, Material const& m, std::shared_ptr<Light> const& h,
                   glm::vec3 const& r, glm::vec3 const& v, glm::vec3 const& l, glm::vec3 const& n);
  Color reflection(Ray const& ray, glm::vec3 const& n, glm::vec3 intP, int depth);
  Color refraction(Material const& m, glm::vec3 const& n, Ray const& ray, glm::vec3 const& intP, int depth);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  Scene scene_;
  glm::vec3 beobachter_;
  glm::vec3 screenCenter_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
