// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"


Renderer::Renderer(unsigned w, unsigned h, std::string const& file,
                    Scene const& scene, glm::vec3 const& be, glm::vec3 const& ce):
  width_(w),
  height_(h),
  colorbuffer_(w*h, Color(0.0, 0.0, 0.0)),
  filename_(file),
  scene_(scene),
  beobachter_(be),
  screenCenter_(ce),
  ppm_(width_, height_){}

void Renderer::render()
{
  //const std::size_t checkersize = 20;
  std::cout<<"screenCenter: "<< screenCenter_.z<<"\n";
  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      Pixel p(x,y);
      /*Pixel passend im Koordinatensystem verschieben, sodass der Ursprung
      /in der Mitte liegt*/
      glm::vec3 screenP{0.0f};
      float w = width_ / 2;
      float h = height_ / 2;
      screenP.x = 1 * (x + (-w));
      screenP.y = -1 * (y + (-h));
      screenP.z = screenCenter_.z;
      // if((x%100 ==0) && (y%100== 0)){
      //   std::cout<<"ScreenP: "<<screenP.x<<", "<<screenP.y<<", "<<screenP.z<<"\n\n";
      // }

      screenP.x -= beobachter_.x;
      screenP.y -= beobachter_.y;
      screenP.z -= beobachter_.z;

      Ray ray(beobachter_, screenP);//beobachter als Fußpunkt, Differenz zum Schirm ist Richtung
      // if((x%100 ==0) && (y%100== 0)){
      //   std::cout<<"x: "<<x;
      //   std::cout<<" y: "<<y;
      //   std::cout<<ray;
      // }
      p.color = color(ray, scene_);

      // if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
      //   p.color = Color(0.0, 1.0, float(x)/height_);
      // } else {
      //   p.color = Color(1.0, 0.0, float(y)/width_);
      // }

      write(p);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::color(Ray const& ray, Scene const& scene){
  bool boxGetroffen = false;
  bool sphereGetroffen = false;

  OptionalHit hitMinB{false, std::numeric_limits<float>::max(), glm::vec3{0.0f}};
  Box nearestBox;

  for(const auto& i: scene.boxes_){
    Box b = *i;
    float distance = 0.0f;
    auto hit = b.intersect(ray, distance);
      if(hit.hit_ && (hit.t_ < hitMinB.t_)){
        hitMinB = hit; //!!!
        nearestBox = *i;
        boxGetroffen = true;
      }
  }
  //über nearestBox color aufrufen

  OptionalHit hitMinS{false, std::numeric_limits<float>::max(), glm::vec3{0.0f}};
  Sphere nearestSphere;

  for(const auto& i: scene.spheres_){
    Sphere s = *i;
    float distance = 0.0f;
    auto hitS = s.intersect(ray, distance);
    if(hitS.hit_ && (hitS.t_ < hitMinS.t_)){
      hitMinS = hitS;
      nearestSphere = *i;
      sphereGetroffen = true;
    }
  }

  if(boxGetroffen){
    return Color{0.8f, 0.2f, 0.4f}; //nearestBox.
  }

  if(sphereGetroffen){
    return Color{0.0f, 0.8f, 0.2f};
  }

  return Color{0.0f};
}

// Color Renderer::comColor(Shape const& shape, Light const& light,
//         Ray const& n, Ray const& l, Ray const&, Ray const& r, Ray const& v){
//   Color i{};
//   Material m = shape.getMaterial();
//   i.r_ = (m.ka_.r * light.ia_.r)+
//         (light.ip_.r*(m.kd_.r*(l*n) + m.ks_.r*pow((r*v),m.m_);
// }

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
