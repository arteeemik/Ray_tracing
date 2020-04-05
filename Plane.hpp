//
// Created by Artem Baryshev on 4/4/20.
//

#ifndef RT__PLANE_HPP_
#define RT__PLANE_HPP_

#include "Point.hpp"
#include "Material.hpp"

struct Plane {
  Plane (Point color_1, Point color_2, int multi, int dist, int coor, bool mirror = false)
  : color_1(color_1)
  , color_2(color_2)
  , multi(multi)
  , dist_(dist)
  , coor(coor)
  , mirror(mirror)
  {}

  void intersect_plane(
      const Point& start_ray,
      const Point& ray,
      Material& material,
      float& nearestDistanceToCrossPoint,
      Point& crossPoint,
      Point& vecCrossPointToCenter) {
    if (fabs(ray[coor]) > 1e-3) {
      float dist = -(start_ray[coor] + float(dist_)) / ray[coor];
      Point pt = start_ray + ray * dist;
      if (dist > 0 && dist < nearestDistanceToCrossPoint) {
        nearestDistanceToCrossPoint = dist;
        crossPoint = pt;
        if (coor == 0) {
          vecCrossPointToCenter = Point(dist_ < 0 ? -1 : 1, 0, 0);
        } else if (coor == 1) {
          vecCrossPointToCenter = Point(0, dist_ < 0 ? -1 : 1, 0);
        } else if (coor == 2) {
          vecCrossPointToCenter = Point(0, 0, dist_ < 0 ? -1 : 1);
        }
        int dist_z = (int(crossPoint[(coor + 1) % 3] + 1000) / multi) % 2;
        int dist_x = (int(crossPoint[(coor + 2) % 3] + 1000) / multi) % 2;

        Point col = (dist_z + dist_x) & 1 ? color_1 : color_2;

        if (mirror) {
          material = MATERIAL_MIRROR;
        } else {
          material = MATERIAL_MATT;
          material.color = col;
        }
      }
    }
  }

  Point color_1;
  Point color_2;
  int multi;
  int coor;
  int dist_;
  bool mirror;
};

#endif //RT__PLANE_HPP_
