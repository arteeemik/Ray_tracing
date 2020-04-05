//
// Created by Artem Baryshev on 3/25/20.
//

#ifndef RT__COLORS_HPP_
#define RT__COLORS_HPP_
#include "Point.hpp"

uint32_t getColorFromPoint(const Point& color) {
  uint32_t first = color[2] < 0 ? 0 : uint32_t(color[2] * RGP_CONSTANT);
  uint32_t second = color[1] < 0 ? 0 : uint32_t(color[1] * RGP_CONSTANT);
  uint32_t third = color[0] < 0 ? 0 : uint32_t(color[0] * RGP_CONSTANT);
  return (first << uint32_t(16)) + (second << uint32_t(8)) + third;
}

void create_texture(
    const Point& point,
    const Point& color_1,
    const Point& color_2,
    const Point& color_3,
    const Point& color_4,
    Material& material,
    int multiplier,
    int param) {
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

#endif //RT__COLORS_HPP_
