//
// Created by Artem Baryshev on 3/30/20.
//

#ifndef RT__FIGURE_HPP_
#define RT__FIGURE_HPP_

#include <cstdio>
#include <fstream>
#include "Hash_map.hpp"
#include "Point.hpp"
#include "Material.hpp"
#include "Triangle_intersection.hpp"
#include "Sphere.hpp"
#include "Constants.hpp"

// ---- Константы -----
constexpr int CNT_NODE = 7000;
constexpr int CNT_THREE_POINTS = 15000;
// ---- Константы -----

struct ThreePoint {
  ThreePoint(){}

  ThreePoint(int a, int b, int c){
    points[0] = a;
    points[1] = b;
    points[2] = c;
  }

  int& operator[](const size_t& ind) {
    return points[ind];
  }

  int points[3];
};

struct MyFigure {
  MyFigure(bool hash_map) {
    hash_map_ = hash_map;
    if (hash_map) {
      FILE* fp = fopen(PATH_TO_POINTS_WOLF, "r");
      float x1, x2, x3, y1, y2, y3, z1, z2, z3;
      while (fscanf(fp, "%f %f %f %f %f %f %f %f %f",
                    &x1, &x2, &x3, &y1, &y2, &y3, &z1, &z2, &z3) > 0) {
        figure_points[{x1, x2, x3}] = {{y1, y2, y3}, {z1, z2, z3}};
      }
      fclose(fp);
    } else {
      Point points_mas[CNT_NODE];
      freopen(PATH_TO_FIGURE, "r", stdin);
      int cnt_points = 0;
      float max_x = -1000, max_y = -1000, max_z = -1000;
      float min_x = 1000, min_y = 1000, min_z = 1000;
      float x, y, z;
      char sym;
      std::cout << "start_read_figure\n";
      int chet = 1;
      while (1) {
        std::cin >> sym;
        if (sym == 'e') {
          break;
        }
        if (chet % 2 == 0) {
          std::cin >> sym;
        }
        chet = (chet + 1) % 2;
        std::cin >> x >> y >> z;
        if (sym == 'n') {
          continue;
        }
        z -= 10;
        y -= 3;
        x -= 4;
        max_x = std::max(x, max_x);
        max_y = std::max(y, max_y);
        max_z = std::max(z, max_z);
        min_x = std::min(x, min_x);
        min_y = std::min(y, min_y);
        min_z = std::min(z, min_z);
        points[sz_points++] = Point(x, y, z);
      }

      sphere_.center = Point((max_x + min_x) / 2, (max_y + min_y) / 2, (max_z + min_z) / 2);
      sphere_.radius = sqrtf(Point(max_x - min_x, max_y - min_y, max_z - min_z)
                                 * Point(max_x - min_x, max_y - min_y, max_z - min_z));

      int x1, x2, x3, f1, f2, f3;
      while (1) {
        std::cin >> sym;
        if (sym == 'e') {
          break;
        }
        scanf("%d//%d %d//%d %d//%d", &x1, &f1, &x2, &f2, &x3, &f3);
        coord[sz_coord++] = ThreePoint(x1, x2, x3);
      }
      fclose(stdin);
      std::cout << "end_read_figure\n";
    }
  }

  void figure_intersection(
      const Point& start_ray,
      const Point& ray,
      Material& material,
      Point& crossPoint,
      Point& vecCrossPointToCenter,
      float& nearestDistanceToCrossPoint) {
    float dist_test;

    if (!sphere_.ray_intersect(start_ray, ray, dist_test)) {
      return;
    }
    Material new_(
        Point({100, 100, 100}).getColorFromRGP(),
        1000, 0, 0, 0.8);
    for (int i = 0; i < sz_coord; ++i) {
      Point one = points[coord[i][0]];
      Point two = points[coord[i][1]];
      Point three = points[coord[i][2]];
      float dist = triangle_intersection(
          start_ray, ray, one,
          two, three);

      if (dist > 1e-3 && dist < nearestDistanceToCrossPoint) {
        new_.color = Point({230, 28, 68}).getColorFromRGP();
        material = new_;
        crossPoint = start_ray + ray * dist;
        nearestDistanceToCrossPoint = dist;
        vecCrossPointToCenter = crossVec(three - one, two - one).normalize();
      }
    }
  }

  ~MyFigure() {
    if (!hash_map_) {
      FILE *fp = fopen(PATH_TO_POINTS_WOLF, "w");
      for (auto it : figure_points) {
        fprintf(fp, "%.27f %.27f %.27f\n%.27f %.27f %.27f\n%.27f %.27f %.27f\n",
                it.first[0], it.first[1], it.first[2],
                it.second.first[0], it.second.first[1], it.second.first[2],
                it.second.second[0], it.second.second[1], it.second.second[2]);
      }
    }
  }

  Sphere sphere_;
  Point points[CNT_NODE];
  int sz_points = 1;
  ThreePoint coord[CNT_THREE_POINTS];
  int sz_coord = 0;
  std::unordered_map <Point, std::pair<Point, Point>, my_hash, equal_point> figure_points;
  bool hash_map_;
  bool active = true;
};

#endif //RT__FIGURE_HPP_
