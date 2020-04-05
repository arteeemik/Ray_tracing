//
// Created by Artem Baryshev on 3/31/20.
//

#ifndef RT__TRIANGLE_INTERSECTION_HPP_
#define RT__TRIANGLE_INTERSECTION_HPP_

#include "Point.hpp"

Point crossVec(const Point& a, const Point& b) {
  return {
      a[1] * b[2] - a[2] * b[1],
      a[2] * b[0] - a[0] * b[2],
      a[0] * b[1] - a[1] * b[0]
  };
}

// ------ Алгоритм Моллера — Трумбора -------
float triangle_intersection(
    const Point& start_ray,
    const Point& ray,
    const Point& node_0,
    const Point& node_1,
    const Point& node_2) {
  Point ray_from_0_to_1 = node_1 - node_0;
  Point ray_from_0_to_2 = node_2 - node_0;

  Point pvec = crossVec(ray, ray_from_0_to_2);
  float det = ray_from_0_to_1 * pvec;

  if (abs(det) < 1e-4) {
    return 0;
  }

  float inv_det = 1 / det;
  Point tvec = start_ray - node_0;
  float u = (tvec * pvec) * inv_det;
  if (u < 0 || u > 1) {
    return 0;
  }

  Point qvec = crossVec(tvec, ray_from_0_to_1);
  float v = ray * qvec * inv_det;
  if (v < 0 || u + v > 1) {
    return 0;
  }
  return ((ray_from_0_to_2 * qvec) * inv_det);
}

#endif //RT__TRIANGLE_INTERSECTION_HPP_
