//
// Created by Artem Baryshev on 4/4/20.
//

#ifndef RT__PICTURE_HPP_
#define RT__PICTURE_HPP_

#include "Point.hpp"
#include "Colors.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Picture {
  Picture(const char* path_to_picture) {
    int some;
    unsigned char *pixmap = stbi_load(path_to_picture, &width, &height, &some, 0);
    date.resize(width * height);
    #pragma omp parallel for
    for (int j = height - 1; j >= 0 ; j--) {
      for (int i = 0; i < width; i++) {
        date[i + j * width] =
            Point(
                pixmap[(i + j * width) * 3],
                pixmap[(i + j * width) * 3 + 1],
                pixmap[(i + j * width) * 3 + 2])
                * (1 / float(RGP_CONSTANT));
      }
    }
    stbi_image_free(pixmap);
  }
  Picture(Point background) : background(background) {}

  Picture() {}

  Point operator[](const size_t& ind) {
    return date[ind];
  }

  void get_pixel_from_ray(const Point& ray, Material& material) {
    if (date.size() == 0) {
      material.color = background;
    } else {
      float percent_width = 0.5 + (atan2(ray[2], ray[0])) / 2 / M_PI;
      float percent_height = 0.5f - asin(ray[1]) / M_PI;

      int width_i = percent_width * width;
      int height_j = percent_height * height;

      width_i = width_i < 0 ? 0 : width_i > width_i - 1 ? width_i - 1 : width_i;
      height_j = height_j < 0 ? 0 : height_j > height_j - 1 ? height_j - 1 : height_j;

      material.color = date[width_i + height_j * width];
    }
  }

  Point background;
  std::vector <Point> date;
  int width;
  int height;
};

#endif //RT__PICTURE_HPP_
