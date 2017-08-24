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
#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>
#include <cmath>
#include <iostream>
#include <limits>
#include <typeinfo>
#include <cstdlib>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file,
                      Scene const& scene, glm::vec3 const& be, glm::vec3 const& ce);

  void render();
  OptionalHit hitBox(Ray const& ray);
  OptionalHit hitSphere(Ray const& ray);
  OptionalHit hitObject(Ray const& ray);
  Color raytracer(Ray const& ray);
  Color compColor(Shape const& shape, glm::vec3 const& n,
  glm::vec3 const& v, glm::vec3 const& schnP);
  void write(Pixel const& p);

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
