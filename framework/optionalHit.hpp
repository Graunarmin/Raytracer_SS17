#ifndef OPTIONALHIT_HPP
#define OPTIONALHIT_HPP

struct OptionalHit{

  OptionalHit():
    hit_{false},
    t_{0.0f},
    intersectionPoint_{0.0f}/*,
    color_{0.0f}*/{}

  OptionalHit(bool hit, float distance, glm::vec3 intP /*,Color color*/):
      hit_{hit},
      t_{distance},
      intersectionPoint_{intP}/*,
      color_{color}*/{}

  // OptionalHit(OptionalHit const& hit):
  //   hit_{hit.hit_},
  //   t_{hit.t_},
  //   intersectionPoint_{hit.intersectionPoint_}{}


  bool hit_;
  float t_;
  glm::vec3 intersectionPoint_;
  //Color color_;
};

#endif //OPTIONALHIT_HPP
