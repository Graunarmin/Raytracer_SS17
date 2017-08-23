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

  Box nearestBox{};
  Sphere nearestSphere{};


//Berechnen der Rays durch jedes einzelne Pixel
void Renderer::render(){

  for (unsigned y = 0; y < height_; ++y){
    for (unsigned x = 0; x < width_; ++x){

      Pixel p(x,y);

      //Pixel Koordinaten für Koordinatensystem umrechnen
      glm::vec3 screenP{0.0f};
      float w = width_ / 2;
      float h = height_ / 2;
      screenP.x = 1 * (x + (-w));
      screenP.y = -1 * (y + (-h));
      screenP.z = screenCenter_.z;

      //Beobachter als Fußpunkt, Differenz zum Schirm ist Richtung
      screenP.x -= beobachter_.x;
      screenP.y -= beobachter_.y;
      screenP.z -= beobachter_.z;

      Ray ray(beobachter_, screenP);

      //Berechnen der Farbe für jedes Pixel
      p.color = raytracer(ray);

      write(p);
    }
  }
  ppm_.save(filename_);
}

//Berechnen der Farbe
Color Renderer::raytracer(Ray const& ray){

 OptionalHit boxGetroffen = hitBox(ray);
 OptionalHit sphereGetroffen = hitSphere(ray);

 //Light currentLight;

 //Licht einlesen
 /*for(const auto& i: scene_.lights_){
   currentLight = *i;
   float distance = 0.0f;
   float rx = ((currentLight.position_.x) - (ray.origin_.x)) / (ray.direction_.x);
   float ry = ((currentLight.position_.y) - (ray.origin_.y)) / (ray.direction_.y);
   float rz = ((currentLight.position_.z) - (ray.origin_.z)) / (ray.direction_.z);

   if((rx == ry) && (ry == rz)){
     lightGetroffen = true;
     nearestLight = *i;
     std::cout<<"-------------Licht wurde getroffen------------\n";
   }

   if(rx == ry || ry == rz || rx == rz){
     lightGetroffen = true;
     std::cout<<"----Licht wurde fast getroffen----\n";
   }

 }*/

 /*if(lightGetroffen){
   return light.ia_ + light.ip_;
 }*/

 //wenn Box und Sphere überlappen: kleinste Distanz
 if(boxGetroffen.hit_ && sphereGetroffen.hit_){
   //Falls Box näher
   if(boxGetroffen.t_ < sphereGetroffen.t_){
     glm::vec3 n = glm::normalize(nearestBox.computeNorm(boxGetroffen));
     glm::vec3 v = glm::normalize(beobachter_ - boxGetroffen.intersectionPoint_);
     //return compColor(boxGetroffen, n, v);
     return compColor(nearestBox, n, v, boxGetroffen.intersectionPoint_);
   }
   //falls Sphere näher
   else{
     glm::vec3 n = glm::normalize(sphereGetroffen.intersectionPoint_ - nearestSphere.getCenter());
     glm::vec3 v = glm::normalize(beobachter_ - sphereGetroffen.intersectionPoint_);
     //return compColor(sphereGetroffen, n, v);
     return compColor(nearestSphere, n, v, sphereGetroffen.intersectionPoint_);
   }
 }

 //Nur Box getroffen
 else if(boxGetroffen.hit_){
  glm::vec3 n = glm::normalize(nearestBox.computeNorm(boxGetroffen));
  glm::vec3 v = glm::normalize(beobachter_ - boxGetroffen.intersectionPoint_);
  return compColor(nearestBox, n, v, boxGetroffen.intersectionPoint_);
 }

 //Nur Sphere getroffen
 else if(sphereGetroffen.hit_){
   glm::vec3 v = glm::normalize(beobachter_ - sphereGetroffen.intersectionPoint_);
   glm::vec3 n = glm::normalize(sphereGetroffen.intersectionPoint_ - nearestSphere.getCenter());
   return compColor(nearestSphere, n, v, sphereGetroffen.intersectionPoint_);
 }

 //Background Farbe
 return Color{0.9f};
}

OptionalHit Renderer::hitBox(Ray const& ray){

  //Berechnen Schnitt Ray durch Pixel mit jeder Box
  OptionalHit boxGetroffen{false, std::numeric_limits<float>::max(), glm::vec3{0.0f}};

  for(const auto& i: scene_.boxes_){
    Box b = *i;
    float distance = 0.0f;
    auto hitB = b.intersect(ray, distance);
    if(hitB.hit_ && (hitB.t_ < boxGetroffen.t_)){
      boxGetroffen = hitB;
      boxGetroffen.nearestShape_ = std::make_shared<Box>(b);
      nearestBox = b;
    }
  }
  return boxGetroffen;
}

OptionalHit Renderer::hitSphere(Ray const& ray){

  //Berechnen Schnitt Ray durch Pixel mit jeder Kugel
  OptionalHit sphereGetroffen{false, std::numeric_limits<float>::max(), glm::vec3{0.0f}};

  for(const auto& i: scene_.spheres_){
    Sphere s = *i;
    float distance = 0.0f;
    auto hitS = s.intersect(ray, distance);
    if(hitS.hit_ && (hitS.t_ < sphereGetroffen.t_)){
      sphereGetroffen = hitS;
      sphereGetroffen.nearestShape_ = std::make_shared<Sphere>(s);
      nearestSphere = s;
    }
  }
  return sphereGetroffen;
}


//Berechnung der Farbe mit Beleuchtungsmodell
Color Renderer::compColor(Shape const& shape, glm::vec3 const& n,
      glm::vec3 const& v, glm::vec3 const& schnP){

   Color i{};
   Color summeDif{0.0f};
   Material m = shape.getMaterial();

   for(const auto& h: scene_.lights_){
     Light j = *h;
     //int delta = 1;
     /*delta 0 = Objekt dazwischen
     delta 1 = kein Objekt*/

     glm::vec3 l = glm::normalize(j.position_ - schnP);
     glm::vec3 r = glm::normalize((2 * (glm::dot(n, l)) * n) - l);

     Ray thomas{schnP, l};
     thomas.origin_ += thomas.direction_ * 0.001f;
     OptionalHit boxObst = hitBox(thomas);
     OptionalHit sphereObst = hitSphere(thomas);

     if(boxObst.hit_ || sphereObst.hit_){
       float lightdist =  glm::length(l);
       if((lightdist < boxObst.t_) || (lightdist < sphereObst.t_)){

         summeDif.r += (j.ip_.r * (m.kd_.r * std::max(glm::dot(l,n), 0.0f) + m.ks_.r * pow(glm::dot(r,v),m.m_)));
         summeDif.g += (j.ip_.g * (m.kd_.g * std::max(glm::dot(l,n), 0.0f) + m.ks_.g * pow(glm::dot(r,v),m.m_)));
         summeDif.b += (j.ip_.b * (m.kd_.b * std::max(glm::dot(l,n), 0.0f) + m.ks_.b * pow(glm::dot(r,v),m.m_)));

       }


       /*float lightdist =  glm::length(l);
       if((lightdist < boxObst.t_) || (lightdist < sphereObst.t_)){
         delta = 1;
       }
     }
     else{
       delta = 1;*/
     }

     i.r += (m.ka_.r * j.ia_.r) + summeDif.r;
     i.g += (m.ka_.g * j.ia_.g) + summeDif.g;
     i.b += (m.ka_.b * j.ia_.b) + summeDif.b;

     /*summeDif.r += (j.ip_.r * delta * (m.kd_.r * std::max(glm::dot(l,n), 0.0f) + m.ks_.r * pow(glm::dot(r,v),m.m_)));
     summeDif.g += (j.ip_.g * delta * (m.kd_.g * std::max(glm::dot(l,n), 0.0f) + m.ks_.g * pow(glm::dot(r,v),m.m_)));
     summeDif.b += (j.ip_.b * delta * (m.kd_.b * std::max(glm::dot(l,n), 0.0f) + m.ks_.b * pow(glm::dot(r,v),m.m_)));*/
   }

   /*for(const auto& u: scene_.lights_){
    Light light = *u;

    i.r += (m.ka_.r * light.ia_.r) + summeDif.r;
    i.g += (m.ka_.g * light.ia_.g) + summeDif.g;
    i.b += (m.ka_.b * light.ia_.b) + summeDif.b;

   }*/

  Color f{};
  f.r = i.r / (i.r +1);
  f.g = i.g / (i.g +1);
  f.b = i.b / (i.b +1);
  return f;
}


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
