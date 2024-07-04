#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/SparseCore>
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "grid_operations.hpp"
#include "stats.hpp"


namespace{
struct Point{
long x ;
long y ;
};
}

void regenerate_2Dgrid( Eigen::MatrixXi & grid, double prob_trap ) {

  int flag_trap = 1 ; 

  std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count()) ;
  std::uniform_real_distribution<double> distrib( 0.0, 1.0) ; 

  grid.setZero() ;

  for ( long idx_row = 0 ; idx_row < grid.rows() ; ++idx_row ){
    for ( long idx_col = 0 ; idx_col < grid.cols() ; ++idx_col ){

      if ( distrib( gen ) < prob_trap )
        grid( idx_row, idx_col ) = flag_trap ; 

    }
  }
}


Eigen::MatrixXd get_distance_lookup_table(size_t grid_size, std::function<double(double)> const& dist_fun ){

  Point center = {static_cast<int>(grid_size/2) , static_cast<int>(grid_size/2) } ;

  Eigen::MatrixXd point_distance(grid_size, grid_size) ; 
  assert(point_distance.rows() == point_distance.cols()) ;

  Eigen::MatrixXi visited (grid_size, grid_size); 
  visited.setZero() ; 

  int num_layers = point_distance.rows() - ( center.x + 1  )  ;

  for(int idx_layer = 0 ; idx_layer < num_layers + 1 ; ++ idx_layer ){
    for (int idx_row = center.x -( idx_layer  ); idx_row < (center.x + 1) + idx_layer  ; ++idx_row ){
      for (int idx_col = center.y -( idx_layer  )  ; idx_col < (center.y + 1 ) + idx_layer  ; ++idx_col ){

        if( visited(idx_row, idx_col) == 1 ) continue ; 

        point_distance(idx_row, idx_col ) = dist_fun(static_cast<double>( idx_layer ) / num_layers)  ;
        visited(idx_row, idx_col) = 1 ; 
      }
    }
  }
  return point_distance ; 
}


template< typename callable>
void modify_2Dgrid_using_custom_function( Eigen::MatrixXi & grid, double prob_trap_old, double prob_trap_new, 
                                         callable is_element_to_be_removed) {


  double const p_diff = ( prob_trap_new - prob_trap_old ) ; 

  std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count())  ;
  std::uniform_int_distribution <int> distrib( 0, grid.rows() - 1 ) ; 

  int const replacement = (p_diff > 0 ) ? 1 : 0 ; // Replace 0 with 1 to increase occupied states and vice versa to decrease occupied states
#ifdef DEBUG_MODE
  static Eigen::MatrixXd observed_replacements(grid.rows(), grid.cols()); 
  [[maybe_unused]] static bool do_once = std::invoke([](){observed_replacements.setZero(); return 1 ;}); 
#endif
  long total_replacements = static_cast<long>(std::abs(p_diff) * grid.size() )  ;

  if (p_diff != 0.0 ) {
    for( long idx_rep = 0 ; idx_rep < total_replacements ;  ){
      long x = distrib(gen) ;
      long y = distrib(gen) ;
      if( is_element_to_be_removed( grid(x, y), x, y, p_diff) ){
        ++idx_rep ;
        grid(x, y ) =  replacement ;
#ifdef DEBUG_MODE
        observed_replacements(x, y) += 1./total_replacements;
#endif
      }
    }
  }
#ifdef DEBUG_MODE
  static int counter = 0 ; 
  ++counter ;
  std::cout << counter << '\n' ;
  if(counter == 89999){
  std::cout << "observed_replacements \n" << observed_replacements << '\n' ;
  }
#endif
}

void modify_2Dgrid( Eigen::MatrixXi & grid, double prob_trap_old, double prob_trap_new ) {

  auto dist_fun = [](double x ){return stats::pexp(x, 5, false) ; }  ;
  static Eigen::MatrixXd dist_table = get_distance_lookup_table(grid.rows(), dist_fun ); 
  [[maybe_unused]] static bool do_once = [&](){ std::cout << dist_table << std::endl ; return 1 ; }();
  std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count())  ;
  std::uniform_real_distribution<> dist ; 

  auto remove_if_not_zero = [&](int grid_element, int rnd_row, int rnd_col, double p_diff) -> bool {
    return  (p_diff >0 ) ? 
  grid_element == 0  && dist(gen) <  dist_table(rnd_row, rnd_col) 
  :
  grid_element != 0  && dist(gen) <  dist_table(rnd_row, rnd_col);
  };

  modify_2Dgrid_using_custom_function(grid,  prob_trap_old , prob_trap_new,
                                      remove_if_not_zero) ;
}



