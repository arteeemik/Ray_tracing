//
// Created by Artem Baryshev on 3/31/20.
//

#ifndef RT__SPHERE_HPP_
#define RT__SPHERE_HPP_

#include "Material.hpp"
#include "Point.hpp"
#include "Picture.hpp"
#include "My_texture.hpp"

struct Sphere {
  Sphere()
      : center(Point())
      , radius(float())
      , material(Material()) {}
  Sphere(Point c, const float& r, Material material)
      : center(c)
      , radius(r)
      , material(material) {}

  Sphere(Point c, float r, Material material, const char* path_to_picture)
      : center(c)
      , radius(r)
      , material(material)
      , picture(path_to_picture) {}

  Sphere(Point c, const float& r, Material material,
         Point color_1,
         Point color_2,
         Point color_3,
         Point color_4,
         int multiplier,
         int param)
      : center(c)
      , radius(r)
      , material(material)
      , my_texture({color_1, color_2, color_3, color_4, multiplier, param}) {}

  bool ray_intersect(
      const Point& start_ray,
      const Point& ray,
      float& nearest_point) const {

    Point VectorToCenter = center - start_ray;
    float vecCos = VectorToCenter * ray;
    float distToNormalFromCenterToRay = VectorToCenter * VectorToCenter - vecCos * vecCos;

    if (distToNormalFromCenterToRay > radius * radius) {
      return false;
    }

    float distFromNormalToIntersection =
        sqrt(radius * radius - distToNormalFromCenterToRay);

    nearest_point = vecCos - distFromNormalToIntersection;
    float farthest_point = vecCos + distFromNormalToIntersection;

    if (nearest_point < 0) nearest_point = farthest_point; // если сфера покрывает точку, откуда пришел луч
    return nearest_point >= 0;
  }

  Point center;
  float radius;
  Material material;
  std::optional<Picture> picture;
  std::optional<MyTexture> my_texture;
};

#endif //RT__SPHERE_HPP_
