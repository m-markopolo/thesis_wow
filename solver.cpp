#include "solver.hpp"
#include <string> 
#include <vector> 
#include <fstream> 
#include <iostream> 
#include <stdlib.h> 

void write_results( std::string const & filename , std::vector<double> const & results ){

  std::ofstream fp ( filename ) ; 

  for ( size_t idx_write = 0 ; idx_write < results.size();  ++idx_write ){

    char const * ending = (  idx_write == results.size() -1 ) ? "" : "," ;
    fp << results[idx_write] << ending ;
  }
}


Solver::~Solver(){
    write_results(m_results_dir + "/Iav.txt", Iav) ;
    write_results(m_results_dir + "/Iav_prime.txt", Iav_prime) ;
    write_results(m_results_dir + "/pmax.txt", pmax) ;
  }

std::vector<double> get_prob_from_file(){
  std::vector<double> results ; 

  std::ifstream read_f( "data/probability_values.txt" );
        std::string cur_line ; 

  while( std::getline(read_f, cur_line, ',') ){
    results.push_back( std::strtod(cur_line.c_str(), nullptr) ) ; 
  }
  return results ; 
}

Solver::Solver(size_t grid_size, int num_rep ) : uf(grid_size) ,grid_size(grid_size), num_rep(num_rep) {

  p_val = get_prob_from_file() ;

  Iav.resize(p_val.size(), 0) ;
  Iav_prime.resize(p_val.size(), 0) ;
  pmax.resize(p_val.size(), 0) ;

}


void Solver::set_results_directory(std::string const & results_directory ){
  m_results_dir = results_directory ;
}

void Solver::get_results(){



    uf.create_2Dgrid( p_val.back()) ;

    uf.hk() ;
    max_cluster_size = uf.relabel_and_get_max_cluster_size();
    update_results(p_val.size() - 1) ;

    uf.clear_sizes() ;

    for ( int idx_prob = p_val.size() - 2 ; idx_prob >= 0 ; --idx_prob){

      double prob_old = p_val[idx_prob + 1]; 
      double prob_new = p_val[idx_prob ];

      uf.replace_nodes_until_new_prob_is_reached( prob_old, prob_new ) ;

      uf.hk() ;
      max_cluster_size = uf.relabel_and_get_max_cluster_size();
      update_results(idx_prob) ;

      uf.clear_sizes() ;


  }
}

void Solver::update_results( size_t idx_prob ){

  long double num_1 =  p_val[ idx_prob  ]* grid_size * grid_size * num_rep  ;  

  for( size_t cluster_size : uf.cluster_sizes() ){

    long double normalized_cluster_size =  cluster_size * (cluster_size /  num_1)    ; 

    Iav[ idx_prob ] += normalized_cluster_size ;

    Iav_prime[ idx_prob ] +=  (cluster_size == max_cluster_size ) ? 
      0 : normalized_cluster_size   ;

  }
    pmax[ idx_prob ] +=  ( max_cluster_size /  num_1  )  ; 
}
