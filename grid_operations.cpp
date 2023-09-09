#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <random>
#include <iostream>
#include <vector>
#include "grid_operations.hpp"

void create_2Dgrid( Eigen::MatrixXi & grid, int grid_size, double prob_trap ) {

  int flag_trap = 1 ; 

	std::uniform_real_distribution <> distrib ( 0, 1) ; 

	grid.setZero() ;

  for ( int idx_row = 0 ; idx_row < grid_size ; ++idx_row ){
    for ( int idx_col = 0 ; idx_col < grid_size ; ++idx_col ){

      if ( distrib( gen ) < prob_trap )
        grid( idx_row, idx_col ) = flag_trap ; 

    }
  }
}

void modify_2Dgrid( Eigen::MatrixXi & grid, int grid_size, double prob_trap_old, double prob_trap_new ) {

	int num_old = ( ( prob_trap_old * grid_size ) * grid_size ) ;
	int num_new = ( ( prob_trap_new * grid_size ) * grid_size ) ;
	int num_diff = abs( num_old - num_new ) ; 

	int look_for = ( ( num_new - num_old ) > 0 ) ? 1 : 0  ;
	int rnd_row, rnd_col ; 

	std::uniform_real_distribution <> distrib ( 0, grid_size - 1 ) ; 


	for (int idx_mod = 0 ; idx_mod < num_diff ; ++idx_mod ){ 

		rnd_row = distrib(gen) ; 
		rnd_col = distrib(gen) ; 
		
		if( grid( rnd_row, rnd_col ) != 1 - look_for )
			grid(rnd_row, rnd_col ) = 1 - look_for ; 

	}
}
