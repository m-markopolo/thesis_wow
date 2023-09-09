#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <random>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <omp.h>

int num_AEM = 4418;  
std::mt19937 gen(num_AEM ) ;



int uf_find( int x, std::vector<int> & labels ) {
	int y = x ; 

	int idx_count = 0 ; 

	while( labels[y] != y ) // find the name of the equivalence class  
		y = labels[y] ; 

	for( idx_count = 0 ; labels[x] != x ; ++idx_count ){
		int z = labels[x] ; 
		labels[x] = y ; // remove the alias 
		x = z ; 
	}
	return y ; 
}

int uf_union ( int x , int y, std::vector<int> & labels ){	
 return labels[ uf_find( x, labels ) ] = uf_find( y, labels ); 
}

int relabel ( Eigen::MatrixXi & grid, std::vector<int> & labels, std::vector<int> & clust_size  ){

	int big_clust = 0 ;

	for( int idx_col = 0 ; idx_col < grid.cols() ; ++idx_col ){
		for( int idx_row = 0 ; idx_row < grid.rows() ; ++idx_row ){

			if ( grid ( idx_row, idx_col ) ){
				grid ( idx_row, idx_col ) = uf_find( grid( idx_row, idx_col ), labels ) ; 

				++clust_size[ grid(idx_row, idx_col ) ] ;
				big_clust = std::max( big_clust, clust_size[ grid(idx_row, idx_col ) ] ) ; 
			}
		}
	}
	return big_clust ; 
}

void bound_cond( int idx_row, int idx_col, int & left, int & up, Eigen::MatrixXi & grid ){

	if ( idx_row == 0 )
		up = 0 ;
	else
		up = grid( idx_row - 1, idx_col ) ; 

	if ( idx_col == 0 )
		left = 0 ;
	else
		left = grid( idx_row , idx_col - 1 ) ;


}




void hk ( std::vector<int> & labels, Eigen::MatrixXi & grid ){

	int left, up,down, right,
			cur_label = 0, nzero ;  

	for( int idx_col = 0 ; idx_col < grid.cols() ; ++idx_col ){
		for( int idx_row = 0 ; idx_row < grid.rows() ; ++idx_row ){

			if ( grid ( idx_row, idx_col ) ){
				bound_cond( idx_row, idx_col, left, up, grid) ;  

				if ( left == 0  && up == 0  ){
					++cur_label ; 
					grid( idx_row , idx_col  ) =  cur_label ; 
					continue ; 

				}else if ( left  && up ){

					
					grid( idx_row, idx_col ) = uf_union( left, up, labels );   // Here, since the canonical names are the same, it doesn't matter which you choose
					continue ; 


				}else{ 
					nzero = left ? left : up ; // find the nonzero 
					grid( idx_row, idx_col ) = uf_find( nzero, labels )  ;
					continue ; 
				}
			}
		}
	}
}

void label_reset( std::vector<int> & labels ){
	for ( int idx_fill = 0 ; idx_fill < labels.size() ; ++idx_fill )
		labels[ idx_fill ] = idx_fill ; 
}

void write_results( std::ofstream & fp , std::vector<double> & results ){

	std::string ending ; 
	for ( int idx_write = 0 ; idx_write < results.size();  ++idx_write ){
		ending = ( idx_write == results.size() -1 ) ? "" : "," ;
		fp << results[idx_write] << ending ;
	}
}

