#include "grid_operations.hpp"
#include "union_find.hpp"

#include <eigen3/Eigen/Dense>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <iostream>
#include <getopt.h>

Eigen::MatrixXd get_distance_lookup_table_test(size_t grid_size ){

  Point center = {static_cast<int>(grid_size/2), static_cast<int>(grid_size/2) } ;

  Eigen::MatrixXd point_distance(grid_size, grid_size) ; 

  Eigen::MatrixXi visited (grid_size, grid_size); 
  visited.setZero() ; 

  int num_layers = point_distance.rows() - ( center.x + 1 )  ;

  for(int layer = 0 ; layer < num_layers + 1 ; ++ layer ){
    for (int row = center.x -( layer  ); row < center.x + layer + 1  ; ++row ){
      for (int col = center.y -( layer  )  ; col < center.y + layer + 1  ; ++col ){

        if( visited(row, col) == 1 ) continue ; 

        point_distance(row, col ) = static_cast<double>( layer ) / num_layers  ;
        visited(row, col) = 1 ; 
      }
    }
  }
  return point_distance ; 
}

int main(int argc, char ** argv){

  size_t grid_size = 1000 ; 
  std::string shortopts = "N:r:" ;
  for( int c = getopt(argc, argv, shortopts.c_str()) ;
  c != -1 ;
  c = getopt(argc, argv, shortopts.c_str()) ) {
  

    switch(c){

      default:
        std::cout << "-N grid size. \n" ;
        break ;
      case 'N' :
        grid_size = ceil(2*(std::atoi(optarg)/2 )) + 1  ;
        break; 

    }
  }

  

  Eigen::MatrixXd grid = get_distance_lookup_table(grid_size) ;

  std::cout << "distance lookup table \n";
  std::cout <<  grid  ;

  for(int i = 0 ; i< 1000 ; ++i ){
   Eigen::MatrixXi grid_test ;
    modify_2Dgrid(grid_test, 1.0, 0.5 ); 
  }
}
