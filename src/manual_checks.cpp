#include "union_find.hpp"
#include "grid_operations.hpp"

#include <eigen3/Eigen/Dense>
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <iostream>
#include <getopt.h>

struct options{
size_t grid_size =100  ;
double p_old = 1.0;
double p_new = 0.5 ;
};
options get_options (int argc, char ** argv){
  options opts ; 
  std::string shortopts = "N:r:" ;
  for( int c = getopt(argc, argv, shortopts.c_str()) ;
  c != -1 ;
  c = getopt(argc, argv, shortopts.c_str()) ) {
  

    switch(c){

      default:
      case 'h':
        [[fallthrough]];
      case 'H':
        std::cout << "-N grid size. \n" ;
        std::cout << "-o old prob. \n" ;
        std::cout << "-n new prob. \n" ;
        std::cout << "-h,H show this message. \n" ;
        std::terminate();
        break ;
      case 'N' :{
        int n =  std::atoi(optarg) ;
        opts.grid_size = n%2 ? n : n + 1 ;
        break; 
      }case 'o' :
        opts.p_old = std::atof(optarg) ;
        break; 
      case 'n' :
        opts.p_new = std::atof(optarg) ;
        break; 

    }
  }
  return opts ;
}


int main(int argc, char ** argv){
  auto [grid_size, p_old, p_new] = get_options(argc, argv) ;

  std::cout << "distance lookup table" << std::endl;
  std::cout <<  get_distance_lookup_table(grid_size) ;

  Eigen::MatrixXi grid_test(grid_size, grid_size) ;
  for(int r = 0 ; r< 10000 ; ++r ){
    for(int i_p = 0 ; i_p < 9 ; ++i_p){
    auto const p = 1.0 - i_p*0.1 ;
    auto const p_ = p - 0.1 ;
    regenerate_2Dgrid(grid_test, p ) ;
    modify_2Dgrid(grid_test, p, p_ ); 
    }
  }
}
