//
// Created by Artem Baryshev on 4/4/20.
//

#ifndef RT__HASH_MAP_HPP_
#define RT__HASH_MAP_HPP_

#include "Point.hpp"

class my_hash{
 public:
  size_t operator()(const Point &k) const{
    return size_t((k[0] + k[1] * 100 + k[2] * 10000) * 1000);
  }
};

struct equal_point {
  bool operator()(const Point& x, const Point& y) const {
    return !(x < y) && !(y < x);
  }
};

#endif //RT__HASH_MAP_HPP_
