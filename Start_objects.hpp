//
// Created by Artem Baryshev on 3/25/20.
//

#ifndef RT__START_OBJECTS_HPP_
#define RT__START_OBJECTS_HPP_

#include "Render.hpp"

std::vector <Sphere> getSpheres(int sceneId) {
  std::vector <Sphere> spheres;
  if (sceneId == 1) {
    spheres.emplace_back(Point(-3, 0, -16), 1.5, MATERIAL_MATT, Point(.7, .2, .1),
                         Point(.1, .6, .7),
                         COLOR_WHITE,
                         COLOR_FUCHSIA,
                         10, 1);
    spheres.emplace_back(Point(-2.0, -2.5, -12), 1.5, MATERIAL_STRANGE);
    spheres.emplace_back(Point(0.8, -0.5, -18), 2.5, MATERIAL_MATT, COLOR_PINK, COLOR_PINK, COLOR_FIO,
                         COLOR_FIO, 5, 2);
    spheres.emplace_back(Point(7.5, 2.75, -20), 3.3, MATERIAL_MIRROR);
  } else if (sceneId == 2) {
    spheres.emplace_back(Point(-6, 3, -20), 3, MATERIAL_MATT, PATH_TO_TEXTURE_MARS);
    spheres.emplace_back(Point(-2.0, -2.5, -12), 1.5, MATERIAL_MATT, PATH_TO_TEXTURE_EARTH);
    spheres.emplace_back(Point(0.8, -0.5, -18), 2.5, MATERIAL_MATT, PATH_TO_TEXTURE_STONE);
    spheres.emplace_back(Point(7.5, 3.75, -20), 3.3, MATERIAL_MATT, PATH_TO_TEXTURE_VENUS);
  }
  return spheres;
}

std::vector <LightRay> getLightRays() {
  std::vector <LightRay> lightRays;
  lightRays.emplace_back(Point(0, 10,  -10), 1.4);
  //lightRays.emplace_back(Point(10, -5,  15), 1.6);
  lightRays.emplace_back(Point(10, 20,  15), 1.5);
  return lightRays;
}

std::vector <Plane> getPlanes(int sceneId) {
  std::vector <Plane> planes;
  if (sceneId == 1) {
    planes.emplace_back(COLOR_WHITE, COLOR_FUCHSIA, 5, -20, 0);
    planes.emplace_back(COLOR_WHITE, Point(.3, .2, .1), 5, 6, 0, true);
    planes.emplace_back(COLOR_WHITE, Point(.1, .1, .1), 5, 40, 2);
    planes.emplace_back(COLOR_WHITE, Point(.1, .2, .2), 5, 4, 1);
    planes.emplace_back(COLOR_WHITE, Point(.4, .2, .3), 5, -30, 1);
  }
  return planes;
}

std::vector <pyramid> getPyramids(int sceneId) {
  std::vector <pyramid> pyramids;
  if (sceneId == 2) {
    pyramids.emplace_back(
        Point(8, -4, -14),
        Point(3, -4, -10),
        Point(4, -1, -12),
        Point(1, -4, -14));
  } else if (sceneId == 1) {
    pyramids.emplace_back(
        Point(0, -2, -12),
        Point(3, -4, -10),
        Point(4, -1, -12),
        Point(1, -4, -14));

    pyramids.emplace_back(
        Point(8, -4, -14),
        Point(3, -4, -10),
        Point(4, -1, -12),
        Point(1, -4, -14), COLOR_WHITE,
        COLOR_WHITE,
        COLOR_PINK,
        COLOR_PINK,
        10, 1);


  }
  return pyramids;
}

#endif //RT__START_OBJECTS_HPP_
