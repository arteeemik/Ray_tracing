//
// Created by Artem Baryshev on 3/24/20.
//

#ifndef RT__RENDER_HPP_
#define RT__RENDER_HPP_
#include <utility>
#include <cmath>
#include <map>
#include <unordered_map>

#include "Global_variables.hpp"
#include "Pyramid_intersection.hpp"

bool searchNearestObject(
    const Point& start_ray,
    const Point& ray,
    Material& material,
    Point& crossPoint,
    Point& vecCrossPointToCenter) {
  float nearestDistanceToCrossPoint = 1e4;
  static float distToCrossPoint;

  // ------ Поиск пересечения луча со сферами -------
  for (auto & sphere : spheres) {
    if (sphere.ray_intersect(start_ray, ray, distToCrossPoint)
      && distToCrossPoint < nearestDistanceToCrossPoint) {

      nearestDistanceToCrossPoint = distToCrossPoint;
      crossPoint = start_ray + ray * nearestDistanceToCrossPoint;

      vecCrossPointToCenter = (crossPoint - sphere.center).normalize();

      material.reflectionLight = sphere.material.reflectionLight;
      material.adoptionLight = sphere.material.adoptionLight;
      material.specularExponentl = sphere.material.specularExponentl;
      material.mirror = sphere.material.mirror;
      material.color = sphere.material.color;

      if (sphere.picture) {
        sphere.picture->get_pixel_from_ray(vecCrossPointToCenter, material);
      } else if (sphere.my_texture) {
        sphere.my_texture->create_texture(crossPoint, material);
      }
    }
  }
  // ------ Поиск пересечения луча со сферами -------

  // ------ Поиск пересечения луча с пирамидами -------
  for (auto& it : pyramids) {
    it.pyramid_intersection(start_ray,
                            ray,
                            material,
                            crossPoint,
                            vecCrossPointToCenter,
                            nearestDistanceToCrossPoint);
  }
  // ------ Поиск пересечения луча с пирамидами -------

  // ------ Поиск пересечения луча с плоскостями -------
  for (auto& plane : planes) {
    plane.intersect_plane(
        start_ray,
        ray,
        material,
        nearestDistanceToCrossPoint,
        crossPoint,
        vecCrossPointToCenter);
  }
  // ------ Поиск пересечения луча с плоскостями -------

  // ------ Поиск пересечения луча с фигурой волка -------
  if (figure.active) {
    if (figure.hash_map_) {
      if (figure.figure_points.find(start_ray + ray) != figure.figure_points.end()) {
        crossPoint = figure.figure_points[start_ray + ray].first;
        vecCrossPointToCenter = figure.figure_points[start_ray + ray].second * -1;
        Point dist = crossPoint - start_ray;
        nearestDistanceToCrossPoint = sqrtf(dist * dist);
        material = MATERIAL_MATT;
        if ((crossPoint[0] < -3.38 && crossPoint[0] > -3.45
            && crossPoint[1] > -2.2 && crossPoint[1] < -2.1) ||
            (crossPoint[0] > -3.6 && crossPoint[0] < -3.51
                && crossPoint[1] > -2.22 && crossPoint[1] < -2.12)) {
          material.color = COLOR_LITTLE_BLACK;
        } else {
          material.color = COLOR_RED;
        }
      }
    } else {
      float last_nearestDistanceToCrossPoint = nearestDistanceToCrossPoint;

      figure.figure_intersection(
          start_ray,
          ray,
          material,
          crossPoint,
          vecCrossPointToCenter,
          nearestDistanceToCrossPoint
      );

      if (std::abs(nearestDistanceToCrossPoint - last_nearestDistanceToCrossPoint) > 1e-4) {
        figure.figure_points[start_ray + ray] = {crossPoint, vecCrossPointToCenter};
      }
    }
  }
  // ------ Поиск пересечения луча с фигурой волка -------

  return nearestDistanceToCrossPoint < 1e4 - 1;
}

// ------ Нормализация цвета -------
Point normalize(const Point& color) {
  float max_ = std::max(std::max(color[0], color[1]), color[2]);
  if (max_ > 1) {
    return {color[0] / max_, color[1] / max_, color[2] / max_};
  } else {
    return color;
  }
}
// ------ Нормализация цвета -------

// ------ Получение отраженного луча от точки пересечения -------
Point make_reflection_ray(const Point& ray, const Point& vecCrossPointToCenter) {
  return ray - vecCrossPointToCenter * 2.f * (ray * vecCrossPointToCenter);
}
// ------ Получение отраженного луча от точки пересечения -------

bool proccesing_shadow(
    const Point& rayFromCrossPointToLight,
    const Point& vecCrossPointToCenter,
    const Point& crossPoint,
    const float distanceRayFromCrossPointToLight) {
  Point shadowCross;
  if (rayFromCrossPointToLight * vecCrossPointToCenter < 0) {
    shadowCross = crossPoint - vecCrossPointToCenter*1e-3;
  } else {
    shadowCross = crossPoint + vecCrossPointToCenter*1e-3;
  }

  Point shadowVecCrossPointToCenter;
  Point shadowCrossPoint;
  Material shadowMaterial;
  return (searchNearestObject(
      shadowCross,
      rayFromCrossPointToLight,
      shadowMaterial,
      shadowCrossPoint,
      shadowVecCrossPointToCenter) &&
      sqrtf((shadowCrossPoint - shadowCross) * (shadowCrossPoint - shadowCross)) < distanceRayFromCrossPointToLight);
}

void proccesing_lights(
    float& lightIntensive,
    float& specularLightIntensity,
    const Point& crossPoint,
    const Point& vecCrossPointToCenter,
    const Point& ray,
    const Material& material) {
  for (auto& it : lightRays) {
    auto rayFromCrossPointToLight = (it.point - crossPoint).normalize();
    float distanceRayFromCrossPointToLight = sqrtf((it.point - crossPoint) * (it.point - crossPoint));

    if (proccesing_shadow(rayFromCrossPointToLight, vecCrossPointToCenter, crossPoint, distanceRayFromCrossPointToLight)) {
      continue;
    }

    lightIntensive += it.intensive * std::max(float(0), rayFromCrossPointToLight * vecCrossPointToCenter);
    float reflactionRay = make_reflection_ray(rayFromCrossPointToLight, vecCrossPointToCenter)*ray;
    if (reflactionRay > 0) {
      specularLightIntensity +=
          pow(reflactionRay,
              material.specularExponentl) * it.intensive;
    }
  }
}

Point cast_ray(
    const Point& start_ray,
    const Point& ray,
    size_t deep = 0) {
  Material material;
  Point vecCrossPointToCenter;
  Point crossPoint;
  if (deep > 4 ||
    !searchNearestObject(
        start_ray,
        ray,
        material,
        crossPoint,
        vecCrossPointToCenter)) {

    // ------ Получение точки фона, так как точки пересечения с объектами -------
    image_background.get_pixel_from_ray(ray, material);
    return material.color;
    // ------ Получение точки фона, так как точки пересечения с объектами -------

    //return COLOR_TURQUISE; // background color
  }

  // ------ Отраженный луч -------
  auto reflectRey = make_reflection_ray(ray, vecCrossPointToCenter).normalize();
  // ------ Отраженный луч -------

  // ------ Сдвиг точки чуть дальше от сферы в ее направлении -------
  Point reflectStart;
  if (reflectRey * vecCrossPointToCenter < 0) {
    reflectStart = crossPoint - vecCrossPointToCenter*1e-3;
  } else {
    reflectStart = crossPoint + vecCrossPointToCenter*1e-3;
  }
  // ------ Сдвиг точки чуть дальше от сферы в ее направлении -------

  Point reflectColor;

  // ------ Если объект не зеркальный, то луч отраженный можно не рассматривать -------
  if (material.mirror > 1e-2) {
    reflectColor = cast_ray(reflectStart, reflectRey, deep + 1);
  } else {
    reflectColor = COLOR_BLACK;
  }
  // ------ Если объект не зеркальный, то луч отраженный можно не рассматривать -------

  // ------ Перебор всех источников света, чтобы понять, насколько светлой сделать точку -------
  float lightIntensive = 0;
  float specularLightIntensity = 0;
  proccesing_lights(lightIntensive, specularLightIntensity, crossPoint, vecCrossPointToCenter, ray, material);
  // ------ Перебор всех источников света, чтобы понять, насколько светлой сделать точку -------

  return material.color * lightIntensive * material.adoptionLight +
      COLOR_ONE * specularLightIntensity * material.reflectionLight +
      reflectColor * material.mirror;
}

#endif //RT__RENDER_HPP_
