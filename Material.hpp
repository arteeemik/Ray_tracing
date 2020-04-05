//
// Created by Artem Baryshev on 3/31/20.
//

#ifndef RT__MATERIAL_HPP_
#define RT__MATERIAL_HPP_

#include "Point.hpp"

struct Material {
  Material()
      : color(Point())
      , specularExponentl(0)
      , adoptionLight(1)
      , reflectionLight (0)
      , mirror(0) {}
  Material(
      Point color,
      int specularExponentl,
      float adoptionLight,
      float reflectionLight,
      float mirror)
      : color(std::move(color))
      , specularExponentl(specularExponentl)
      , adoptionLight(adoptionLight)
      , reflectionLight(reflectionLight)
      , mirror(mirror){}
  Point color;
  int specularExponentl;
  float adoptionLight;
  float reflectionLight;
  float mirror;
};

#endif //RT__MATERIAL_HPP_
