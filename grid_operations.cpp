#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/SparseCore>
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include "grid_operations.hpp"



void regenerate_2Dgrid( Eigen::MatrixXi & grid, double prob_trap ) {

  int flag_trap = 1 ; 

  std::mt19937 gen(1234) ;
  std::uniform_real_distribution<double> distrib( 0.0, 1.0) ; 

  grid.setZero() ;

  for ( long idx_row = 0 ; idx_row < grid.rows() ; ++idx_row ){
    for ( long idx_col = 0 ; idx_col < grid.cols() ; ++idx_col ){

      if ( distrib( gen ) < prob_trap )
        grid( idx_row, idx_col ) = flag_trap ; 

    }
  }
}
Eigen::MatrixXd get_distance_lookup_table(size_t grid_size ){

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


template< typename callable>
void modify_2Dgrid_using_custom_function( Eigen::MatrixXi & grid, double prob_trap_old, double prob_trap_new, callable is_element_to_be_removed) {


  double p_diff = ( prob_trap_new - prob_trap_old ) ; 

  std::mt19937 gen(1234) ;
  std::uniform_int_distribution <> distrib( 0, grid.rows() - 1 ) ; 


  int replacement = (p_diff > 0 ) ? 1 : 0 ; // Replace 0 with 1 to increase occupied states and vice versa to decrease occupied states

  if (p_diff != 0.0 ) {
    for( long idx_rep = 0 ; idx_rep < static_cast<long>(std::abs(p_diff) * grid.size() )  ;  ){


      long rnd_row = distrib(gen) ;
      long rnd_col = distrib(gen) ;


      if( is_element_to_be_removed( grid(rnd_row, rnd_col), rnd_row, rnd_col, p_diff) == true ){


        grid(rnd_row, rnd_col ) =  replacement ;
        ++idx_rep ;

      }
    }
  }
}

void modify_2Dgrid( Eigen::MatrixXi & grid, double prob_trap_old, double prob_trap_new ) {

  static  Eigen::MatrixXd dist_table = get_distance_lookup_table(grid.rows()); 
  std::mt19937 gen(1234) ;
  std::uniform_real_distribution<> dist ; 

  modify_2Dgrid_using_custom_function(grid, prob_trap_old, prob_trap_new, 
                                      [&]
                                      (int grid_element, int rnd_row, int rnd_col, double p_diff) -> bool{
                                      return ( 
                                        (p_diff >0 ) ? 
                                        grid_element == 0  && (dist(gen) <  dist_table(rnd_row, rnd_col)  ) 
                                      :
                                        grid_element != 0  &&   dist(gen) <  dist_table(rnd_row, rnd_col)  );
                                      }
                                      ) ;
}

//  std::cout << grid  << "\n\n" ; }



