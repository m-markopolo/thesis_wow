#include "grid_operations.hpp"
#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <random>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <omp.h>


void update_results( 

	std::vector<double>	results_Iav (p_val.size(), 0 ) ; 
	std::vector<double>	results_Iav_prime (p_val.size(), 0 ) ; 
	std::vector<double>	results_pmax (p_val.size(), 0 ) ; 


		for ( size_t idx_c = 0  ; idx_c < clust_size.size() ; ++idx_c  ){

			m = clust_size[ idx_c ] ; 
			if ( m == 0 )
				continue ;
			
			results_Iav[ idx_prob ] +=  ( m /  num_rep ) * ( m / num_1 )  ;  

			if (m == big_clust ){
				continue ; 
			}else{
				results_Iav_prime[ idx_prob ] +=  ( m  / num_rep ) * ( m  / num_1 ) ;  
			}
		}

		results_pmax[ idx_prob ] +=  big_clust / ( num_1 * num_rep ) ; 


}



	std::vector<int> labels ( num_labels, 0 ) ;
	std::vector <int> clust_size( labels.size(), 0) ;

	for ( size_t idx_rep = 0 ; idx_rep < num_rep ; ++idx_rep ){

			double prob_trap = p_val[ p_val.size() - 1] ; 
			create_2Dgrid( grid, grid_size, prob_trap) ;

		for ( size_t idx_prob = p_val.size() - 1 ; idx_prob >= 0   ; --idx_prob ){
		
//		std::cout << idx_prob << "\n" ; 

			double prob_trap_new = p_val[ idx_prob - 1 ] ; 
			double prob_trap_old = p_val[ idx_prob ] ; 

			label_reset( labels ) ; 

			modify_2Dgrid( grid, grid_size, prob_trap_old, prob_trap_new ) ;
			hk( labels, grid) ;

			big_clust = relabel ( grid, labels, clust_size  );

			num_1 =  ( prob_trap_old  * grid_size * grid_size  ) ;

			std::fill( clust_size.begin(), clust_size.end(), 0 ) ; 

			}
		}
		write_results( fp_Iav , results_Iav ) ;
		write_results( fp_Iav_prime , results_Iav_prime ) ;
		write_results( fp_pmax, results_pmax ) ;

int main(){

	int grid_size = 100 ; 
	double prob_trap ;
	
	std::ofstream fp_Iav ("results/Iav.txt") ; 
	std::ofstream fp_Iav_prime ("results/Iav_prime.txt") ; 
	std::ofstream fp_pmax ("results/pmax.txt") ; 

	std::vector <double> p_val { 
		0.1,
		0.2,
		0.3,
		0.4,
		0.5,
		0.55,
		0.56,
		0.57,
		0.58,
  	0.59, 
		0.6,
		0.61,
		0.62,
		0.63, 0.64, 0.65,
		0.7,
		0.8
	} ; 

	int num_labels = grid_size * grid_size / 4  ; 



	int num_rep = 1000 ; 
	double num_1 ;  
	int big_clust = 0 ; 


	int m ; 

	Eigen::MatrixXi grid( grid_size , grid_size ) ; 
	grid << Eigen::MatrixXi::Zero( grid_size , grid_size ) ; 

}
