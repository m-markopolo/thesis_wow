#include "grid_operations.hpp"
#include "union_find.hpp"
#include "solver.hpp"

#include <bits/getopt_core.h>
#include <iostream>
#include <unistd.h>
#include <getopt.h>


int get_closest_odd_num_including_self(int n){
  return (n%2) ? n +1  : n ; 
}

int main(int argc, char ** argv){

  size_t grid_size = 1000 ; 
  int num_rep = 10 ; 

  std::string shortopts = "N:r:" ;
  for( int c = getopt(argc, argv, shortopts.c_str()) ; c != -1 ; c = getopt(argc, argv, shortopts.c_str()) ) {

    switch(c){

      default:{
        std::cout << "-N grid size. \n" ;
        std::cout << "-r number of repetitions . \n" ;
        break ;
      }
      case 'N' :{

        grid_size = std::atoi(optarg) ;
        break; 

      }
      case 'r' :{
        num_rep = std::atoi(optarg) ;
        break; 
      }
    }
  }
  grid_size = get_closest_odd_num_including_self(grid_size) ;


  Solver solve(grid_size, num_rep) ;
  solve.set_results_directory("results") ;

  for (int idx_rep = 0 ; idx_rep < num_rep ; ++idx_rep )
    solve.get_results() ;
}
