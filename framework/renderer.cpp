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
      p.color = color(ray, scene_);

      write(p);
    }
  }
  ppm_.save(filename_);
}


 //Berechnen der Farbe
Color Renderer::color(Ray const& ray, Scene const& scene){
  
  bool boxGetroffen = false;
  bool sphereGetroffen = false;
  bool lightGetroffen = false;
  Light currentLight;
  glm::vec3 schnittpunktNearestB;
  glm::vec3 schnittpunktNearestS;

  //Light light{"coolesLicht", glm::vec3{0.0f}, Color{1.0f, 0.9f, 0.9f}, Color{0.5f}};
  //Light nearestLight;
  
  //Licht einlesen
  for(const auto& i: scene.lights_){
    currentLight = *i;
    /*float distance = 0.0f;
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
    }*/

  }

  //Berechnen Schnitt Ray durch Pixel mit jeder Box
  OptionalHit hitMinB{false, std::numeric_limits<float>::max(), glm::vec3{0.0f}};
  Box nearestBox;

  for(const auto& i: scene.boxes_){
    Box b = *i;
    float distance = 0.0f;
    auto hitB = b.intersect(ray, distance);
      if(hitB.hit_ && (hitB.t_ < hitMinB.t_)){
        hitMinB = hitB; 
        nearestBox = *i;
        boxGetroffen = true;
        schnittpunktNearestB = hitB.intersectionPoint_;
      }
  }

  //Berechnen Schnitt Ray durch Pixel mit jeder Kugel
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
      schnittpunktNearestS = hitS.intersectionPoint_;
    }
  }

  /*if(lightGetroffen){
    return light.ia_ + light.ip_;
  }*/

  //wenn Box und Sphere überlappen: kleinste Distanz
  if(boxGetroffen && sphereGetroffen){

    //Falls Box näher
    if(hitMinB.t_ < hitMinS.t_){
      //glm::vec3 l = glm::normalize(currentLight.position_ - schnittpunktNearestB);
    
      glm::vec3 n = glm::normalize(nearestBox.computeNorm(hitMinB));

      glm::vec3 v = glm::normalize(beobachter_ - schnittpunktNearestB);

      //glm::vec3 r = glm::normalize((2 * (glm::dot(n, l)) * n) - l);
    
      return compColor(nearestBox, currentLight, n, v, schnittpunktNearestB);
    }
    //falls Sphere näher
    /*else{
      return compColor(nearestSphere, light);
    }*/
  }

  //Nur Box getroffen
  else if(boxGetroffen){

    //glm::vec3 l = glm::normalize(currentLight.position_ - schnittpunktNearestB);
    
    glm::vec3 n = glm::normalize(nearestBox.computeNorm(hitMinB));

    glm::vec3 v = glm::normalize(beobachter_ - schnittpunktNearestB);

    //glm::vec3 r = glm::normalize((2 * (glm::dot(n, l)) * n) - l);
    
    return compColor(nearestBox, currentLight, n, v, schnittpunktNearestB);
    //return compColor(nearestBox, currentLight, n, l, r, v);
  }

  //Nur Sphere getroffen
  /*else if(sphereGetroffen){
    return compColor(nearestSphere, light);
  }*/

  //Background Farbe
  return Color{0.9f};
}

//Berechnung der Farbe mit Beleuchtungsmodell
Color Renderer::compColor(Shape const& shape, Light const& light,
glm::vec3 const& n, glm::vec3 const& v, glm::vec3 const& schnP){
   Color i{};
   Color summeDif{};
   Material m = shape.getMaterial();

   //Nur für Box!!
   for(const auto& h: scene_.lights_){
     Light j = *h;

     glm::vec3 l = glm::normalize(light.position_ - schnP);
     glm::vec3 r = glm::normalize((2 * (glm::dot(n, l)) * n) - l);
     
     summeDif.r += (j.ip_.r * (m.kd_.r * glm::dot(l,n) + m.ks_.r * pow(glm::dot(r,v),m.m_)));
     summeDif.g += (j.ip_.g * (m.kd_.g * glm::dot(l,n) + m.ks_.g * pow(glm::dot(r,v),m.m_)));
     summeDif.b += (j.ip_.b * (m.kd_.b * glm::dot(l,n) + m.ks_.b * pow(glm::dot(r,v),m.m_)));
   }

   i.r = (m.ka_.r * light.ia_.r) + summeDif.r;
   i.g = (m.ka_.g * light.ia_.g) + summeDif.g;
   i.b = (m.ka_.b * light.ia_.b) + summeDif.b;
  
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
