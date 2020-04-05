//
// Created by Artem Baryshev on 4/4/20.
//

#ifndef RT__CONSTANTS_HPP_
#define RT__CONSTANTS_HPP_
#include "Material.hpp"
#include "Picture.hpp"
#include "Point.hpp"
#include "Sphere.hpp"

// ------ Цвета -------
const Point COLOR_ORANGE = Point({204, 110, 16}).getColorFromRGP();
const Point COLOR_BLUES = Point({30, 50, 199}).getColorFromRGP();
const Point COLOR_PINK = Point({212, 143, 163}).getColorFromRGP();
const Point COLOR_FIO = Point({94, 115, 219}).getColorFromRGP();
const Point COLOR_FUCHSIA = Point({112, 101, 47}).getColorFromRGP();
const Point COLOR_TURQUISE = Point(23, 201, 214).getColorFromRGP();
const Point COLOR_WHITE = Point({.3, .3, .3});
const Point COLOR_ONE = Point({1, 1, 1});
const Point COLOR_BLACK = Point({0, 0, 0});
const Point COLOR_RED = Point({230, 28, 68}).getColorFromRGP();
const Point COLOR_LITTLE_BLACK = Point({26, 22, 23}).getColorFromRGP();

// ------ Цвета -------

// ------ Материал -------
const Material MATERIAL_MATT;
const Material MATERIAL_MIRROR(Point(), 1000, 0.0, 10, 0.8);
const Material MATERIAL_STRANGE(COLOR_PINK, 800, 0.8, 10, 0.2);
// ------ Материал -------

// ------ Пути к файлам -------
const char* PATH_TO_FIGURE = "../wolf_v2.obj";
const char* PATH_TO_BACKGROUND = "../ESO_-_Milky_Way.jpg";
const char* PATH_TO_TEXTURE_STONE = "../ground-texture.jpg";
const char* PATH_TO_TEXTURE_MARS = "../Mars-Phobos.jpg";
const char* PATH_TO_TEXTURE_EARTH = "../2k_earth_nightmap.jpg";
const char* PATH_TO_TEXTURE_VENUS = "../2k_venus_surface.jpg";
const char* PATH_TO_POINTS_WOLF = "../figure_points_wolf.txt";
// ------ Пути к файлам -------

// ------ Разрешение картины -------
constexpr int WIDTH = 1500;
constexpr int HEIGHT = 1200;
// ------ Разрешение картины -------

// ------ Константы -------
constexpr bool HASH_MAP = true;
// ------ Константы -------

#endif //RT__CONSTANTS_HPP_
