//
// Created by Artem Baryshev on 3/31/20.
//

#ifndef RT__POINT_HPP_
#define RT__POINT_HPP_
#include <tuple>

// ------- Константы -------
constexpr int RGP_CONSTANT = 255;
// ------- Константы -------

float pow(float num, int step) noexcept {
  float res = 1;
  while (step) {
    if (step & 1) {
      res *= num;
      --step;
    } else {
      num *= num;
      step >>= 1;
    }
  }
  return res;
}

struct Point {
  Point()
  {}

  Point(float a1, float a2, float a3)
  {
    dots[0] = a1;
    dots[1] = a2;
    dots[2] = a3;
  }

  bool operator<(const Point& x) const {
    std::tuple <float, float, float> first({dots[0], dots[1], dots[2]}),
    second({x.dots[0], x.dots[1], x.dots[2]});
    return first < second;
  }

  float& operator[](const size_t& ind) {
    return dots[ind];
  }

  const float& operator[](const size_t& ind) const {
    return dots[ind];
  }

  Point operator-(const Point& another) const {
    const Point& now = *this;
    return Point(
        now[0] - another[0],
        now[1] - another[1],
        now[2] - another[2]);
  }

  Point operator+(const Point& another) const {
    const Point& now = *this;
    return Point(
        now[0] + another[0],
        now[1] + another[1],
        now[2] + another[2]);
  }

  float operator*(const Point& another) const {
    const Point& now = *this;
    return
        now[0] * another[0] +
            now[1] * another[1] +
            now[2] * another[2];
  }

  Point operator*(const float& num) const {
    const Point& now = *this;
    return Point(
        now[0] * num,
        now[1] * num,
        now[2] * num);
  }

  Point& getColorFromRGP() {
    Point& now = *this;
    now[0] /= RGP_CONSTANT;
    now[1] /= RGP_CONSTANT;
    now[2] /= RGP_CONSTANT;
    return now;
  }

  Point& normalize() {
    Point& now = *this;
    float value = sqrt(
        pow(now[0], 2) +
            pow(now[1], 2) +
            pow(now[2], 2));
    for (int i = 0; i <= 2; ++i) {
      now[i] /= value;
    }
    return now;
  }

  float dots[3];
};

#endif //RT__POINT_HPP_
