#include "grid_operations.hpp"
#include "union_find.hpp"
#include "solver.hpp"

#include <bits/getopt_core.h>
#include <iostream>
#include <unistd.h>
#include <getopt.h>



int main(int argc, char ** argv){

  size_t grid_size = 1000 ; 
  int num_rep = 10 ; 

  std::string shortopts = "N:r:" ;
  for( int c = getopt(argc, argv, shortopts.c_str()) ; c != -1 ; c = getopt(argc, argv, shortopts.c_str()) ) {

    switch(c){

      default:
        std::cout << "-N grid size. \n" ;
        break ;
      case 'N' :

        grid_size = std::atoi(optarg) ;
        break; 

      case 'r' :
        num_rep = std::atoi(optarg) ;
        break; 
    }
  }

  Solver solve(grid_size, num_rep) ;
  solve.set_results_directory("results") ;

  for (size_t idx_rep = 0 ; idx_rep < num_rep ; ++idx_rep )
    solve.get_results() ;
}
