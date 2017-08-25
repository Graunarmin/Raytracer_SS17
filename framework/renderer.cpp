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

  //erstellt optionalHit vom nächsten Schnittpunkt mit nächstem Objekt,
  //gespeichert werden, ob Treffer, die Distanz, der Schnittpunkt und das Objekt
 OptionalHit nearestH = hitObject(ray);

 //Normale und Vektor zum Betrachter, um Farbe zu berechnen
 if(nearestH.hit_){
   glm::vec3 n = nearestH.nearestShape_->computeNorm(nearestH);
   glm::vec3 v = glm::normalize(beobachter_ - nearestH.intersectionPoint_);
   return compColor(nearestH, n, v);
 }
 //Background Farbe
 return Color{0.9f};
}

OptionalHit Renderer::hitObject(Ray const& ray){

  OptionalHit nearestHit{false, std::numeric_limits<float>::infinity(), glm::vec3{0.0f}};

  for(auto const& i: scene_.shapes_){
    float distance = 0.0f;
    auto currentHit = i -> intersect(ray, distance);
    if(currentHit.hit_&&(currentHit.t_ < nearestHit.t_)){
      nearestHit = currentHit;
      nearestHit.nearestShape_ = i;//std::make_shared<Box>(i); *i -> createPointer());
    }
  }
  return nearestHit;
}


//Berechnung der Farbe mit Beleuchtungsmodell
Color Renderer::compColor(OptionalHit const& nH, glm::vec3 const& n,
      glm::vec3 const& v/*, glm::vec3 const& intP*/){

   Color i{0.0f};
   Color summeDif{0.0f};
   Material m = nH.nearestShape_ -> getMaterial();
   glm::vec3 intP = nH.intersectionPoint_;

   for(auto const& h: scene_.lights_){
     Light j = *h;

     glm::vec3 l = glm::normalize(j.position_ - intP);
     glm::vec3 r = glm::normalize((2 * (glm::dot(n, l)) * n) - l);

     Ray lightRay{intP, l};
     lightRay.origin_ += /*lightRay.direction_*/n * 0.001f;

     OptionalHit obstacle = hitObject(lightRay);

     if(obstacle.hit_){
       float lightDist =  glm::length(l);
       if(lightDist < obstacle.t_){
         //dann liegt nichts dazwischen!
         summeDif.r += (j.ip_.r * ((m.kd_.r * std::max(glm::dot(l,n), 0.0f)) + (m.ks_.r * pow(glm::dot(r,v),m.m_))));
         summeDif.g += (j.ip_.g * ((m.kd_.g * std::max(glm::dot(l,n), 0.0f)) + (m.ks_.g * pow(glm::dot(r,v),m.m_))));
         summeDif.b += (j.ip_.b * ((m.kd_.b * std::max(glm::dot(l,n), 0.0f)) + (m.ks_.b * pow(glm::dot(r,v),m.m_))));
       }//if zu
     }//if zu
    //  i.r += (m.ka_.r * j.ia_.r) + summeDif.r;
    //  i.g += (m.ka_.g * j.ia_.r) + summeDif.g;
    //  i.b += (m.ka_.b * j.ia_.r) + summeDif.b;
   }//for zu

  //EIN ambientes Licht pro Szene wird in der Szenenbeschreibung eingelesen!
   i.r += (m.ka_.r * scene_.ambientLight_.ia_.r) + summeDif.r;
   i.g += (m.ka_.g * scene_.ambientLight_.ia_.g) + summeDif.g;
   i.b += (m.ka_.b * scene_.ambientLight_.ia_.b) + summeDif.b;

  Color f{0.0f};
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
