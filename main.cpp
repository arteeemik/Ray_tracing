#include <iostream>
#include <cstdint>

#include <vector>
#include <omp.h>
#include <ctime>

#include "Bitmap.h"
#include "Render.hpp"
#include "Colors.hpp"
#include "Start_objects.hpp"
#include "Read_params.hpp"
#include "Constants.hpp"

int main(int argc, const char** argv)
{
  read_params(argc, argv);
  omp_set_num_threads(threads);
  if (sceneId == 3) {
    return 0;
  }
  spheres = getSpheres(sceneId);
  lightRays = getLightRays();
  planes = getPlanes(sceneId);
  pyramids = getPyramids(sceneId);

  if (sceneId == 1) {
    image_background = Picture(COLOR_FUCHSIA);
  } else if (sceneId == 2) {
    figure.active = false;
    image_background = Picture(PATH_TO_BACKGROUND);
  }

  constexpr float fov = 1;
  std::vector<Point> framebuffer(WIDTH * HEIGHT);

  Point ray_ox = Point(tanf(fov / 2.0f), 0, 0);
  Point ray_oy = Point(0, tanf(fov / 2.0f) / (float(WIDTH) / HEIGHT), 0);
  #pragma omp parallel for
  for (size_t j = 0; j < HEIGHT; ++j) {
    for (size_t i = 0; i < WIDTH; ++i) {
      //std::cout << i + j * WIDTH << "\n";
      float x = 2.0f * i / (float(WIDTH) - 1) - 1;
      float y = 2.0f * j / (float(HEIGHT) - 1) - 1;

      Point ray = (ray_ox * x + ray_oy * y + Point(0, 0, -1)).normalize();
      Point ans = cast_ray(Point(0, 0, 0), ray);

      framebuffer[i + j * WIDTH] =
          framebuffer[i + j * WIDTH] + ans;

      // ------ Устранение ступенчатости методом прибавления пикселя к соседним клеткам -------
      for (int z = -1; z < 2; ++z) {
        for (int s = -1; s < 2; ++s) {
          if (i > 0 && j > 0 && j < HEIGHT - 1 && i < WIDTH - 1) {
            if (s == 0 || z == 0) {
              framebuffer[i + z + (j + s) * WIDTH] =
                  framebuffer[i + z + (j + s) * WIDTH] + ans * 0.4;
            } else {
              framebuffer[i + z + (j + s) * WIDTH] =
                  framebuffer[i + z + (j + s) * WIDTH] + ans * 0.3;
            }
          }
        }
      }
      // ------ Устранение ступенчатости методом прибавления пикселя к соседним клеткам -------
    }
  }
  
  std::vector<uint32_t> image(WIDTH * HEIGHT);
  #pragma omp parallel for
  for (size_t i = 0; i < HEIGHT * WIDTH; ++i) {
    image[i] = getColorFromPoint(normalize(framebuffer[i] * (1.0f / 4)));
  }

  SaveBMP(outFilePath.c_str(), image.data(), WIDTH, HEIGHT);

  return 0;
}