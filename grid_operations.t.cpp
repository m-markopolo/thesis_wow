#include "grid_operations.hpp"

#include <eigen3/Eigen/Dense>
//#define CATCH_CONFIG_MAIN
//#include <catch2/catch.hpp>

#include <iostream>
#include <getopt.h>

Eigen::MatrixXd get_distance_lookup_table_test(size_t grid_size ){

  Point center = {static_cast<int>(grid_size/2), static_cast<int>(grid_size/2) } ;

  Eigen::MatrixXd point_distance(grid_size, grid_size) ; 

  Eigen::MatrixXi visited (grid_size, grid_size); 
  visited.setZero() ; 

  int num_layers = point_distance.rows() - ( center.x + 1 )  ;

  for(int idx_layer = 0 ; idx_layer < num_layers + 1 ; ++ idx_layer ){
    for (int idx_row = center.x -( idx_layer  ); idx_row < center.x + idx_layer + 1  ; ++idx_row ){
      for (int idx_col = center.y -( idx_layer  )  ; idx_col < center.y + idx_layer + 1  ; ++idx_col ){

        if( visited(idx_row, idx_col) == 1 ) continue ; 

        point_distance(idx_row, idx_col ) = static_cast<double>( idx_layer ) / num_layers  ;
        visited(idx_row, idx_col) = 1 ; 
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

        grid_size = std::atoi(optarg) ;
        break; 

    }
  }


  grid_size = ( grid_size % 2 == 0) ? 
    grid_size + 1 : 
    grid_size ;

  Eigen::MatrixXd grid = get_distance_lookup_table(grid_size) ;

  std::cout <<  grid  ;
}
