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
 Color y {0.9f};
 y.r = (y.r * scene_.ambientLight_.ia_.r);
 y.g = (y.g * scene_.ambientLight_.ia_.g); 
 y.b = (y.b * scene_.ambientLight_.ia_.b); 
 return y;
 //return Color{1.0f, 1.0f, 0.5f};
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


//Achtung noch in Arbeit!! zwei mal gleiche Funktion aber leicht unterschiedlich!! Oben = alte version, Unten = neu

//Berechnung der Farbe mit Beleuchtungsmodell
/*Color Renderer::compColor(OptionalHit const& nH, glm::vec3 const& n,
      glm::vec3 const& v){

   Color i{0.0f};
   Color summeDif{0.0f};
   Material m = nH.nearestShape_ -> getMaterial();
   glm::vec3 intP = nH.intersectionPoint_;

   for(auto const& h: scene_.lights_){
     Light j = *h;

     glm::vec3 l = glm::normalize(j.position_ - intP);
     glm::vec3 r = glm::normalize((2 * (glm::dot(n, l)) * n) - l);

     Ray lightRay{intP, l};
     lightRay.origin_ += n * 0.01f;

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

    if(!obstacle.hit_){
      summeDif.r += (j.ip_.r * ((m.kd_.r * std::max(glm::dot(l,n), 0.0f)) + (m.ks_.r * pow(glm::dot(r,v),m.m_))));
      summeDif.g += (j.ip_.g * ((m.kd_.g * std::max(glm::dot(l,n), 0.0f)) + (m.ks_.g * pow(glm::dot(r,v),m.m_))));
      summeDif.b += (j.ip_.b * ((m.kd_.b * std::max(glm::dot(l,n), 0.0f)) + (m.ks_.b * pow(glm::dot(r,v),m.m_))));
    }
    //i.r += (m.ka_.r * j.ia_.r) + summeDif.r;
    //i.g += (m.ka_.g * j.ia_.g) + summeDif.g;
    //i.b += (m.ka_.b * j.ia_.b) + summeDif.b;
   }//for zu

  //EIN ambientes Licht pro Szene wird in der Szenenbeschreibung eingelesen!
   i.r = (m.ka_.r * scene_.ambientLight_.ia_.r) + summeDif.r;
   i.g = (m.ka_.g * scene_.ambientLight_.ia_.g) + summeDif.g;
   i.b = (m.ka_.b * scene_.ambientLight_.ia_.b) + summeDif.b;

  Color f{0.0f};
  f.r = i.r / (i.r +1);
  f.g = i.g / (i.g +1);
  f.b = i.b / (i.b +1);
  return f;
}*/

//Berechnung der Farbe mit Beleuchtungsmodell
Color Renderer::compColor(OptionalHit const& nH, glm::vec3 const& n, glm::vec3 const& v){

   Color i{0.0f};
   Color summeDif{0.0f};
   Material m = nH.nearestShape_ -> getMaterial();
   glm::vec3 intP = nH.intersectionPoint_;

   for(auto const& h: scene_.lights_){

     glm::vec3 l = glm::normalize(h->position_ - intP);
     glm::vec3 u = h->position_ - intP;
     glm::vec3 r = glm::normalize((2 * (glm::dot(n, l)) * n) - l);

     Ray lightRay{intP, l};
     lightRay.origin_ += intP + l * 0.01f; 
     // lightRay.origin_ += n * 0.01f;

     int distance = glm::length(intP - h->position_);
     OptionalHit obstacle = hitObject(lightRay);

     //Objekt liegt hinter Lichtquelle, also kein Schatten
     if(glm::length(l) < obstacle.t_){

       pointLight(summeDif, m, h, r, v, l, n);
     }
     else{ //Eigentlich Schatten! Es geht einfach viel zu selten hier rein...
         std::cout << "gehe rein \n";
     }
   }//for zu

    //EIN ambientes Licht pro Szene wird in der Szenenbeschreibung eingelesen!
    ambientLight(summeDif, m, i);

    i.r = i.r / (i.r +1);
    i.g = i.g / (i.g +1);
    i.b = i.b / (i.b +1);

    return i;
}//compColor zu

void Renderer::ambientLight(Color const& summeDif, Material const& m, Color& i){

  i.r = (m.ka_.r * scene_.ambientLight_.ia_.r) + summeDif.r;
  i.g = (m.ka_.g * scene_.ambientLight_.ia_.g) + summeDif.g;
  i.b = (m.ka_.b * scene_.ambientLight_.ia_.b) + summeDif.b;
}

void Renderer::pointLight(Color& summeDif, Material const& m, std::shared_ptr<Light> const& h, 
                          glm::vec3 const& r, glm::vec3 const& v, glm::vec3 const& l, glm::vec3 const& n){
  summeDif.r += (h->ip_.r * ((m.kd_.r * std::max(glm::dot(l,n), 0.0f)) + (m.ks_.r * pow(glm::dot(r,v),m.m_))));
  summeDif.g += (h->ip_.g * ((m.kd_.g * std::max(glm::dot(l,n), 0.0f)) + (m.ks_.g * pow(glm::dot(r,v),m.m_))));
  summeDif.b += (h->ip_.b * ((m.kd_.b * std::max(glm::dot(l,n), 0.0f)) + (m.ks_.b * pow(glm::dot(r,v),m.m_))));
}




//------------------------------------------------------------//


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
