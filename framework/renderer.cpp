#include "renderer.hpp"


Renderer::Renderer(Scene const& scene/*, glm::vec3 const& ce*/):
  width_(scene.width_),
  height_(scene.height_),
  colorbuffer_(width_*height_, Color(0.0, 0.0, 0.0)),
  filename_(scene.filename_),
  scene_(scene),
  //screenCenter_(ce),
  ppm_(width_, height_){}

//Berechnen der Rays durch jedes einzelne Pixel
void Renderer::render(){

  for (unsigned y = 0; y < height_; ++y){
    for (unsigned x = 0; x < width_; ++x){

      int depth = 3;

      Ray ray = scene_.camera_.compRay(x, y, width_, height_);

      Pixel p(x,y);

      p.color = raytracer(ray, depth);


      //--------------------------------
      //Ohne Kamera mit Beobachter in (0,0,0):
      //Pixel Koordinaten für Koordinatensystem umrechnen
      // glm::vec3 screenP{0.0f};
      // float w = width_ / 2;
      // float h = height_ / 2;
      // screenP.x = 1 * (x + (-w));
      // screenP.y = 1 * (y + (-h));
      // screenP.z = screenCenter_.z;
      //
      // //Beobachter als Fußpunkt, Differenz zum Schirm ist Richtung
      // screenP.x -= beobachter_.x;
      // screenP.y -= beobachter_.y;
      // screenP.z -= beobachter_.z;
      //
      // Ray ray(beobachter_, screenP);
      //--------------------------------

      //Berechnen der Farbe für jedes Pixel

      write(p);
    }
  }
  ppm_.save(filename_);
}

//Berechnen der Farbe
Color Renderer::raytracer(Ray const& ray, int depth){

 //erstellt optionalHit vom nächsten Schnittpunkt mit nächstem Objekt,
 //gespeichert werden, ob Treffer, die Distanz, der Schnittpunkt und Pointer auf das Objekt
 OptionalHit nearestH = hitObject(ray);

 //Normale und Vektor zum Betrachter, um Farbe zu berechnen
 if(nearestH.hit_){
   glm::vec3 n = nearestH.nearestShape_->computeNorm(nearestH);               //Normalen Vektor
   glm::vec3 v = glm::normalize(ray.origin_ - nearestH.intersectionPoint_);   //Vektor zum Betrachter
   return compColor(nearestH, n, v, depth, ray);
 }

 //Background Farbe
 Color y {1.0f};
 y.r = (y.r * scene_.ambientLight_.ia_.r);
 y.g = (y.g * scene_.ambientLight_.ia_.g);
 y.b = (y.b * scene_.ambientLight_.ia_.b);
 return y;
}

OptionalHit Renderer::hitObject(Ray const& ray){

  OptionalHit nearestHit{false, std::numeric_limits<float>::infinity(), glm::vec3{0.0f}};

  for(auto const& i: scene_.composite_->shapes_){
    float distance = 0.0f;
    auto currentHit = i -> intersect(ray, distance);
    if(currentHit.hit_&&(currentHit.t_ < nearestHit.t_)){
      nearestHit = currentHit;
      nearestHit.nearestShape_ = i;
    }
  }
  return nearestHit;
}

//Berechnung der Farbe mit Beleuchtungsmodell
Color Renderer::compColor(OptionalHit const& nH, glm::vec3 const& n, glm::vec3 const& v, int depth, Ray const& ray){

   Color i{0.0f};
   Color summeDif{0.0f};
   Color reflectionC{1.0f};
   Color refractionC{1.0f};
   Material m = nH.nearestShape_ -> getMaterial();
   glm::vec3 intP = nH.intersectionPoint_;

   //Schatten
   for(auto const& h: scene_.lights_){

     glm::vec3 l = glm::normalize(h->position_ - intP);               //l = Vektor zu Licht
     glm::vec3 r = glm::normalize((2 * (glm::dot(n, l)) * n) - l);    //r = l gespiegelt an n

     //Schatten Ray
     Ray lightRay{intP, l};
     lightRay.origin_ += n * 0.01f;

     //Distanz von Schnittpunkt zu Licht
     float distance = glm::length(intP - h->position_);

     OptionalHit obstacle = hitObject(lightRay);

     //Objekt liegt hinter Lichtquelle, also kein Schatten -> d.h. Punktlicht muss berechnet werden
     if(distance < obstacle.t_){
       pointLight(summeDif, m, h, r, v, l, n);
     }
     //Falls im Schatten nur Ambient
   }//for zu

   //Reflektion:
   //Depth = Anzahl der rekursiven Aufrufe, je mehr desto mehr Spiegelungen in Spiegelungen
   if(depth > 0){
      reflectionC = reflection(ray, n, intP, depth);
      depth -= 1;
   }

   //Refraktion:
   //Opacity = Transparenz, je höher desto durchsichtiger
   if(m.opacity_ > 1){
     refractionC = refraction(m, n, ray, intP, depth);
   }

    //EIN ambientes Licht pro Szene wird in der Szenenbeschreibung eingelesen!
    ambientLight(summeDif, m, i);

    //Reflektion & Refraktion
    i.r += reflectionC.r * m.ks_.r * refractionC.r * m.opacity_;
    i.g += reflectionC.g * m.ks_.g * refractionC.g * m.opacity_;
    i.b += reflectionC.b * m.ks_.b * refractionC.b * m.opacity_;

    //Colormapping
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

Color Renderer::reflection(Ray const& ray, glm::vec3 const& n, glm::vec3 const& intP, int depth){
    glm::vec3 r = glm::normalize(glm::reflect(ray.direction_, n));    //Spiegeln Vektor von Betrachter an n
    Ray reflectionRay{intP, r};
    reflectionRay.origin_ += n * 0.01f;

    return raytracer(reflectionRay, depth);
}

Color Renderer::refraction(Material const& m, glm::vec3 const& n, Ray const& ray, glm::vec3 const& intP, int depth){

   float inAngle = glm::dot(ray.direction_, n);

  if(inAngle <= m.ri_){ //Ansonsten TIR
    glm::vec3 t = glm::refract(ray.direction_, n, m.ri_);

    Ray refractionRay{intP, t};

    refractionRay.origin_ += n * 0.01f;

    return raytracer(refractionRay, depth);
  }
  else{
    return 1.0f;
  }
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
