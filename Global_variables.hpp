//
// Created by Artem Baryshev on 4/4/20.
//

#ifndef RT__GLOBAL_VARIABLES_HPP_
#define RT__GLOBAL_VARIABLES_HPP_
#include "Figure.hpp"
#include "Point.hpp"
#include "Material.hpp"
#include "Constants.hpp"
#include "Sphere.hpp"
#include "Triangle_intersection.hpp"
#include "Pyramid_intersection.hpp"
#include "Colors.hpp"
#include "Constants.hpp"
#include "Light_ray.hpp"
#include "Plane.hpp"

// ------ Фигура -------
MyFigure figure(HASH_MAP);
// ------ Фигура -------

// ------ Картина -------
Picture image_background;
// ------ Картина -------

// ------ Объекты -------
std::vector <Sphere> spheres;
std::vector <LightRay> lightRays;
std::vector <Plane> planes;
std::vector <pyramid> pyramids;
// ------ Объекты -------

#endif //RT__GLOBAL_VARIABLES_HPP_
