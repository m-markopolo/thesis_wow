#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include "grid_operations.hpp"

void create_2Dgrid( Eigen::MatrixXi & grid, double prob_trap ) {

  int flag_trap = 1 ; 

  std::mt19937 gen(1234) ;
  std::uniform_real_distribution<double> distrib( 0.0, 1.0) ; 

  grid.setZero() ;

  for ( size_t idx_row = 0 ; idx_row < grid.rows() ; ++idx_row ){
    for ( size_t idx_col = 0 ; idx_col < grid.cols() ; ++idx_col ){

      if ( distrib( gen ) < prob_trap )
        grid( idx_row, idx_col ) = flag_trap ; 

    }
  }
}
bool is_element_to_be_removed( int grid_element, double p_diff ){

  if(p_diff > 0 ){
    return grid_element == 0 ;
  }else {
    return grid_element != 0 ;
  }
}
void modify_2Dgrid( Eigen::MatrixXi & grid, double prob_trap_old, double prob_trap_new ) {


  double p_diff = ( prob_trap_new - prob_trap_old ) ; 

  std::mt19937 gen(1234) ;
  std::uniform_int_distribution <> distrib( 0, grid.rows() - 1 ) ; 


  int replacement = (p_diff > 0 ) ? 1 : 0 ; // Replace 0 with 1 to increase occupied states and vice versa to decrease occupied states

  for( size_t idx_rep = 0 ; idx_rep < std::abs(p_diff) * grid.size()  ;  ){


    size_t rnd_row = distrib(gen) ;
    size_t rnd_col = distrib(gen) ;

    if( is_element_to_be_removed( grid(rnd_row, rnd_col), p_diff ) == true ){

      grid(rnd_row, rnd_col ) =  replacement ;
      ++idx_rep ;

    }
  }
}

