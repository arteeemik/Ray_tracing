//
// Created by Artem Baryshev on 4/4/20.
//

#ifndef RT__MY_TEXTURE_HPP_
#define RT__MY_TEXTURE_HPP_

#include "Point.hpp"

struct MyTexture {
  MyTexture (
      Point color_1,
      Point color_2,
      Point color_3,
      Point color_4,
      int multiplier,
      int param)
      : color_1(color_1)
      , color_2(color_2)
      , color_3(color_3)
      , color_4(color_4)
      , multiplier(multiplier)
      , param(param) {}

  void create_texture(const Point& point, Material& material) {
    int a = point[1] * multiplier + 1000;
    int b = point[0] * multiplier + 1000;
    if (a & param && b & param) {
      material.color = color_1;
    } else if (a & param && !(b & param)) {
      material.color = color_2;
    } else if (!(a & param) && b & param) {
      material.color = color_3;
    } else {
      material.color = color_4;
    }
  }

  Point color_1;
  Point color_2;
  Point color_3;
  Point color_4;
  int multiplier;
  int param;
};

#endif //RT__MY_TEXTURE_HPP_
