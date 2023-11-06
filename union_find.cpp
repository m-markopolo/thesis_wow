#include "/usr/include/eigen3/Eigen/Dense"
#include "union_find.hpp"
#include "grid_operations.hpp"

#include <random>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <omp.h>





void Union_find::create_2Dgrid( double prob_trap ){
  regenerate_2Dgrid( m_grid, prob_trap ) ;
}
void Union_find::replace_nodes_until_new_prob_is_reached( double prob_trap_old, double prob_trap_new ) {
  modify_2Dgrid( m_grid, prob_trap_old, prob_trap_new ) ;
}

int Union_find::uf_find( int x ) {

	int y = x ; 

	while(m_labels[y] != y ){
    m_labels[y] = m_labels[m_labels[y]] ;
		y = m_labels[y] ;
	}
	return y ; 
}


int Union_find::uf_union ( int x , int y ){	
 return m_labels[ uf_find( x ) ] = uf_find( y ); 
}

int Union_find::relabel_and_get_max_cluster_size(){

	int big_clust = 0 ;

	for( int idx_col = 0 ; idx_col < m_grid.cols() ; ++idx_col ){
		for( int idx_row = 0 ; idx_row < m_grid.rows() ; ++idx_row ){

			if ( m_grid ( idx_row, idx_col ) ){
				m_grid ( idx_row, idx_col ) = uf_find( m_grid( idx_row, idx_col )) ; 

				++m_clust_size[ m_grid(idx_row, idx_col ) ] ;
				big_clust = std::max( big_clust, m_clust_size[ m_grid(idx_row, idx_col ) ] ) ; 
			}
		}
	}
	return big_clust ; 
}

void Union_find::bound_cond( int idx_row, int idx_col, int & left, int & up  ){

  up = (idx_row == 0 ) ? 0 : m_grid(idx_row -1, idx_col ) ;
  left = (idx_col == 0 ) ? 0 : m_grid(idx_row , idx_col - 1 ) ;

}


void Union_find::hk (){

	int left, up, cur_label = 0 ;

	for( int idx_col = 0 ; idx_col < m_grid.cols() ; ++idx_col ){
		for( int idx_row = 0 ; idx_row < m_grid.rows() ; ++idx_row ){

			if ( m_grid ( idx_row, idx_col ) ){
				bound_cond( idx_row, idx_col, left, up ) ;  

				if ( left == 0  && up == 0  ){
					++cur_label ; 
					m_grid( idx_row , idx_col  ) =  cur_label ; 
					continue ; 

				}else if ( left  && up ){

					m_grid( idx_row, idx_col ) = uf_union( left, up );   // Here, since the canonical names are the same, it doesn't matter which you choose
					continue ; 


				}else{ 
					int nzero = left ? left : up ; // find the nonzero 
					m_grid( idx_row, idx_col ) = uf_find( nzero )  ;
					continue ; 
				}
			}
		}
	}
}


