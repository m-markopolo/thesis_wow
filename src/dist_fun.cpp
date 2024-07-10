#include "dist_fun.hpp"
#include "stats.hpp"
double dist_fun([[maybe_unused]] double x) {
  return stats::pexp(x, 1.0, false) ; 
}

