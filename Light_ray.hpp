//
// Created by Artem Baryshev on 4/4/20.
//

#ifndef RT__LIGHT_RAY_HPP_
#define RT__LIGHT_RAY_HPP_
#include "Point.hpp"

struct LightRay {
  LightRay(Point point, float intensive)
      : point(point)
      , intensive(intensive) {};

  Point point;
  float intensive;
};

#endif //RT__LIGHT_RAY_HPP_
