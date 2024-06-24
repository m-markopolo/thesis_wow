#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "union_find.hpp"
#include <vector>
#include <string>


void write_results( std::string const & filename , std::vector<double> const & results );

class Solver{

private:


  Union_find uf ;
  size_t grid_size  = 0;
  int num_rep = 0 ; 

  std::vector <double> p_val ;

  std::vector<double>	Iav ;
  std::vector<double>	Iav_prime ;
  std::vector<double>	pmax ;

  size_t max_cluster_size = 0 ;
  std::string  m_results_dir = {} ;
  void update_results(size_t idx_prob ) ;

public :

  Solver(size_t grid_size, int num_rep);
  ~Solver();

  void set_results_directory(std::string const & results_directory );
  void get_results();



};




#endif
