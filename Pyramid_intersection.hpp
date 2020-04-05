//
// Created by Artem Baryshev on 3/31/20.
//

#ifndef RT__PYRAMID_INTERSECTION_HPP_
#define RT__PYRAMID_INTERSECTION_HPP_

#include "Point.hpp"
#include "Triangle_intersection.hpp"

struct pyramid {
  pyramid (
      const Point& x1,
      const Point& x2,
      const Point& x3,
      const Point& x4) : new_(Material(Point({100, 100, 100}).getColorFromRGP(), 1000, 0, 0, 0.8)) {
    dots[0] = x1;
    dots[1] = x2;
    dots[2] = x3;
    dots[3] = x4;
    numbers = {
        {0, {1, 2}},
        {0, {1, 3}},
        {0, {2, 3}},
        {1, {2, 3}}};
  }
  pyramid (
      const Point& x1,
      const Point& x2,
      const Point& x3,
      const Point& x4,
      Point color_1,
      Point color_2,
      Point color_3,
      Point color_4,
      int multiplier,
      int param)
      : my_texture({color_1, color_2, color_3, color_4, multiplier, param}) {
    dots[0] = x1;
    dots[1] = x2;
    dots[2] = x3;
    dots[3] = x4;
    numbers = {
        {0, {1, 2}},
        {0, {1, 3}},
        {0, {2, 3}},
        {1, {2, 3}}};
    new_ = MATERIAL_MATT;
  }

  void pyramid_intersection(
      const Point& start_ray,
      const Point& ray,
      Material& material,
      Point& crossPoint,
      Point& vecCrossPointToCenter,
      float& nearestDistanceToCrossPoint) {
    for (auto& it : numbers) {
      float dist = triangle_intersection(
          start_ray, ray, dots[it.first],
          dots[it.second.first], dots[it.second.second]);
      if (dist > 1e-3 && dist < nearestDistanceToCrossPoint) {
        material = new_;
        crossPoint = start_ray + ray * dist;
        if (my_texture) {
          my_texture->create_texture(crossPoint, material);
        }
        nearestDistanceToCrossPoint = dist;
        vecCrossPointToCenter = crossVec(
            dots[it.second.second] - dots[it.first],
            dots[it.second.first] - dots[it.first]).normalize();
      }
    }
  }

  std::vector <std::pair<int, std::pair<int, int>>> numbers;
  Point dots[4];
  Material new_;
  std::optional<MyTexture> my_texture;
};

#endif //RT__PYRAMID_INTERSECTION_HPP_
