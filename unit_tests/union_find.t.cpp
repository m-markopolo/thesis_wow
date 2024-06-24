#include "union_find.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

TEST_CASE("test1"){

  Eigen::MatrixXi grid {
    {0,1,1,0},
    {0,0,1,0},
    {1,0,1,0},
    {0,1,0,1}
  } ;
Union_find uf(grid) ;
  uf.hk() ;
  uf.relabel_and_get_max_cluster_size();

  CHECK(uf.get_grid() ==
  Eigen::MatrixXi {
    {0,2,2,0},
    {0,0,2,0},
    {1,0,2,0},
    {0,3,0,4}
  });
}
TEST_CASE("test2"){

  Eigen::MatrixXi grid {
    {0,1,1,0},
    {0,1,1,0},
    {0,1,1,0},
    {1,0,0,1}
  } ;
Union_find uf(grid) ;
  uf.hk() ;
  uf.relabel_and_get_max_cluster_size();

  CHECK(uf.get_grid() ==
  Eigen::MatrixXi {
    {0,2,2,0},
    {0,2,2,0},
    {0,2,2,0},
    {1,0,0,3}
  });
}
