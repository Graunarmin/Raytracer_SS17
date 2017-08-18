#ifndef OPTIONALHIT_HPP
#define OPTIONALHIT_HPP

struct OptionalHit{

  OptionalHit():
    hit_{false},
    t_{0.0f}{}

  OptionalHit(bool hit, float distance):
      hit_{hit},
      t_{distance}{}

  bool rayHits() const{
    return hit_;
  }

  float getDistance() const{
    return t_;
  }

  bool hit_;
  float t_;
};

#endif //OPTIONALHIT_HPP
